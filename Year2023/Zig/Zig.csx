#define TRACE
using System.Net.Http;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.IO.Compression;

public static void CopyAll(DirectoryInfo source, DirectoryInfo target)
{
    Directory.CreateDirectory(target.FullName);

    // Copy each file into the new directory.
    foreach (FileInfo fi in source.GetFiles())
    {
        //Console.WriteLine(@"Copying {0}\{1}", target.FullName, fi.Name);
        fi.CopyTo(Path.Combine(target.FullName, fi.Name), true);
    }

    // Copy each subdirectory using recursion.
    foreach (DirectoryInfo diSourceSubDir in source.GetDirectories())
    {
        DirectoryInfo nextTargetSubDir =
            target.CreateSubdirectory(diSourceSubDir.Name);
        CopyAll(diSourceSubDir, nextTargetSubDir);
    }
}

sealed record ZigVersion
{
    [JsonPropertyName("version")]
    public string Version { get; set; } = string.Empty;
    [JsonPropertyName("date")]
    public string Date { get; set; } = string.Empty;
    [JsonPropertyName("x86_64-windows")]
    public ZigRelease Win64 { get; set; } = new();
    [JsonPropertyName("x86_64-linux")]
    public ZigRelease Linux64 { get; set; } = new();
}

sealed record ZigRelease
{
    [JsonPropertyName("tarball")]
    public string DownloadUrl { get; set; } = string.Empty;
    [JsonPropertyName("shasum")]
    public string Checksum { get; set; } = string.Empty;
    [JsonPropertyName("size")]
    public string Size { get; set; } = string.Empty;
}

sealed record LocalVersion
{
    public string Version { get; set; } = string.Empty;
    public string Date { get; set; } = string.Empty;
}

var OutputDir = new DirectoryInfo(@"C:\Dev\tools\Zig");
WriteLine("Zig dir: " + OutputDir.FullName);
if (!OutputDir.Exists)
{
    throw new DirectoryNotFoundException("Output dir not found: " + OutputDir.FullName);
}

var HttpClient = new HttpClient();
HttpClient.Timeout = TimeSpan.FromSeconds(30.0d);

var Request = new HttpRequestMessage(HttpMethod.Get, "https://ziglang.org/download/index.json");
Request.Headers.Add("Accept", "application/json");

HttpResponseMessage Response = HttpClient.Send(Request);
string ResponseBody = await Response.Content.ReadAsStringAsync();
Response = null;

JsonElement Result = JsonSerializer.Deserialize<JsonElement>(ResponseBody);
List<ZigVersion> ZigDownloads = new();

int Index = 0;
foreach(JsonProperty current in Result.EnumerateObject())
{
    ZigVersion CurrentVersion = JsonSerializer.Deserialize<ZigVersion>(current.Value.GetRawText().Trim());
    if (current.Name != "master")
    {
        CurrentVersion.Version = current.Name;
    }
    ZigDownloads.Add(CurrentVersion);
    Index++;
}

var ChosenVersion = ZigDownloads[0];
WriteLine($"Latest master version: {ChosenVersion.Version} | {ChosenVersion.Date}");

var LocalVersionFile = new FileInfo(Path.Combine(OutputDir.FullName, "VERSION.json"));
DateOnly LatestAvailable = DateOnly.Parse(ChosenVersion.Date);
DateOnly LocalDate = DateOnly.MinValue;

if (LocalVersionFile.Exists)
{
    LocalVersion LocalVersionInfo = JsonSerializer.Deserialize<LocalVersion>(File.ReadAllText(LocalVersionFile.FullName));
    LocalDate = DateOnly.Parse(LocalVersionInfo.Date);
    WriteLine($"Local version: {LocalVersionInfo.Version} | {LocalVersionInfo.Date}");
}

if (LatestAvailable <= LocalDate)
{
    WriteLine("No need to update, exiting...");
    return;
}

WriteLine("Online version newer than local, fetching...");
var DownloadRequest = new HttpRequestMessage(HttpMethod.Get, ChosenVersion.Win64.DownloadUrl);
Request.Headers.Add("Accept", "application/zip");

HttpResponseMessage DownloadResponse = HttpClient.Send(DownloadRequest);
DownloadResponse.EnsureSuccessStatusCode();
Trace.Assert(DownloadResponse.Content.Headers.ContentLength == Convert.ToInt64(ChosenVersion.Win64.Size));

WriteLine("Done");

WriteLine("Extracting files...");
var NewestVersionContent = new ZipArchive(DownloadResponse.Content.ReadAsStream(), System.IO.Compression.ZipArchiveMode.Read);
NewestVersionContent.ExtractToDirectory(OutputDir.FullName);

WriteLine("Copying files out of extracted dir into output dir root");
var ZigDir = OutputDir.GetDirectories().First();
CopyAll(ZigDir, OutputDir);
ZigDir.Delete(true);

LocalVersion LocalVersionInfo = new()
{
    Version = ChosenVersion.Version,
    Date = ChosenVersion.Date
};

File.WriteAllText(OutputDir.FullName + "/VERSION.json", JsonSerializer.Serialize(LocalVersionInfo));
WriteLine("All done");