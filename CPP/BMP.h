
#define BMPID 0x4D42
#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t fileType = BMPID; //jedinstvena oznaka bmp fajla
    uint32_t fileSize = 0; //velicina fajla u bajtovima
    uint16_t unused1 = 0;
    uint16_t unused2 = 0;
    uint32_t data_offset = 0;           // Start position of pixel data (bytes from the beginning of the file)
};

struct BMPInfoHeader {
    uint32_t headerSize = 0; //DIB header size
    int32_t width = 0; //sirina slike u pikselima
    int32_t height = 0; //visina slike u pikselima

    uint16_t planes = 1; //
    uint16_t bitsPerPixel = 0;
    uint32_t compression = 0;
    uint32_t image_size = 0; // koristi se ako je kompresovana slika ovako je nula
    int32_t x_pixels_per_meter = 0;
    int32_t y_pixels_per_meter = 0;
    uint32_t colors_used = 0;
    uint32_t colors_important = 0;    // No. of colors used for displaying the bitmap. If 0 all colors are required
};

struct BMPColorHeader {
    uint32_t red_mask = 0x00ff0000;         // Bit maska za crveni kanal
    uint32_t green_mask = 0x0000ff00;       // Bit maska za zeleni kanak
    uint32_t blue_mask = 0x000000ff;        // Bit maska za plavi kanal
    uint32_t alpha_mask = 0xff000000;       // Bit maska za alfa kanal
    uint32_t color_space_type = 0x73524742;
    uint32_t unused[12] = { 0 };       // Unused data for sRGB color space
};
#pragma pack(pop)
