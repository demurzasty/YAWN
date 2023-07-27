#include <YAWN/Graphics/S3TC.hpp>

#include <rgbcx.hpp>

using namespace YAWN;

static void Ensure() {
	rgbcx::init(rgbcx::bc1_approx_mode::cBC1Ideal);
}

void S3TC::BC1(const void* uncompressedPixels, int uncompressedSize, int stride, void* compressedPixels) {
	Ensure();

	struct Color {
		unsigned char channels[4];
	};

	struct Block {
		Color colors[2];
	};

	const Color* pixels = reinterpret_cast<const Color*>(uncompressedPixels);
	Block* blocks = reinterpret_cast<Block*>(compressedPixels);

	Color inputBlock[16];

	const int width = stride / 4;
	const int blocksX = width / 4;
	const int height = uncompressedSize / stride;

	for (int y = 0u; y < height; y += 4) {
		for (int x = 0u; x < width; x += 4) {
			inputBlock[0] = pixels[y * width + x];
			inputBlock[1] = pixels[y * width + x + 1];
			inputBlock[2] = pixels[y * width + x + 2];
			inputBlock[3] = pixels[y * width + x + 3];

			inputBlock[4] = pixels[(y + 1) * width + x];
			inputBlock[5] = pixels[(y + 1) * width + x + 1];
			inputBlock[6] = pixels[(y + 1) * width + x + 2];
			inputBlock[7] = pixels[(y + 1) * width + x + 3];

			inputBlock[8] = pixels[(y + 2) * width + x];
			inputBlock[9] = pixels[(y + 2) * width + x + 1];
			inputBlock[10] = pixels[(y + 2) * width + x + 2];
			inputBlock[11] = pixels[(y + 3) * width + x + 3];

			inputBlock[12] = pixels[(y + 3) * width + x];
			inputBlock[13] = pixels[(y + 3) * width + x + 1];
			inputBlock[14] = pixels[(y + 3) * width + x + 2];
			inputBlock[15] = pixels[(y + 3) * width + x + 3];

			const int by = y / 4;
			const int bx = x / 4;

			rgbcx::encode_bc1(10, &blocks[by * blocksX + bx], (const unsigned char*)&inputBlock, true, false);
		}
	}
}

Array<unsigned char> S3TC::BC1(const Ref<Image>& image) {
	Array<unsigned char> compressedPixels((image->GetInfo().GetWidth() * image->GetInfo().GetHeight()) / 2);
	BC1(image->GetData().GetData(), image->GetData().GetSizeInBytes(), image->GetInfo().GetWidth() * 4, compressedPixels.GetData());
	return compressedPixels;
}

void S3TC::BC3(const void* uncompressedPixels, int uncompressedSize, int stride, void* compressedPixels) {
	Ensure();

	struct Color {
		unsigned char channels[4];
	};

	struct Block {
		Color colors[4];
	};

	const Color* pixels = reinterpret_cast<const Color*>(uncompressedPixels);
	Block* blocks = reinterpret_cast<Block*>(compressedPixels);

	Color inputBlock[16];

	const int width = stride / 4;
	const int blocksX = width / 4;
	const int height = uncompressedSize / stride;

	for (int y = 0u; y < height; y += 4) {
		for (int x = 0u; x < width; x += 4) {
			inputBlock[0] = pixels[y * width + x];
			inputBlock[1] = pixels[y * width + x + 1];
			inputBlock[2] = pixels[y * width + x + 2];
			inputBlock[3] = pixels[y * width + x + 3];

			inputBlock[4] = pixels[(y + 1) * width + x];
			inputBlock[5] = pixels[(y + 1) * width + x + 1];
			inputBlock[6] = pixels[(y + 1) * width + x + 2];
			inputBlock[7] = pixels[(y + 1) * width + x + 3];

			inputBlock[8] = pixels[(y + 2) * width + x];
			inputBlock[9] = pixels[(y + 2) * width + x + 1];
			inputBlock[10] = pixels[(y + 2) * width + x + 2];
			inputBlock[11] = pixels[(y + 3) * width + x + 3];

			inputBlock[12] = pixels[(y + 3) * width + x];
			inputBlock[13] = pixels[(y + 3) * width + x + 1];
			inputBlock[14] = pixels[(y + 3) * width + x + 2];
			inputBlock[15] = pixels[(y + 3) * width + x + 3];

			const int by = y / 4;
			const int bx = x / 4;

			rgbcx::encode_bc3(10, &blocks[by * blocksX + bx], (const unsigned char*)&inputBlock);
		}
	}
}

Array<unsigned char> S3TC::BC3(const Ref<Image>& image) {
	Array<unsigned char> compressedPixels((image->GetInfo().GetWidth() * image->GetInfo().GetHeight()));
	BC3(image->GetData().GetData(), image->GetData().GetSizeInBytes(), image->GetInfo().GetWidth() * 4, compressedPixels.GetData());
	return compressedPixels;
}

void S3TC::BC4(const void* uncompressedPixels, int uncompressedSize, int stride, void* compressedPixels) {
	Ensure();

	struct Color {
		unsigned char channels[4];
	};

	struct Block {
		Color colors[2];
	};

	const unsigned char* pixels = reinterpret_cast<const unsigned char*>(uncompressedPixels);
	Block* blocks = reinterpret_cast<Block*>(compressedPixels);

	unsigned char inputBlock[16];

	const int width = stride / 1;
	const int blocksX = width / 4;
	const int height = uncompressedSize / stride;

	for (int y = 0u; y < height; y += 4) {
		for (int x = 0u; x < width; x += 4) {
			inputBlock[0] = pixels[y * width + x];
			inputBlock[1] = pixels[y * width + x + 1];
			inputBlock[2] = pixels[y * width + x + 2];
			inputBlock[3] = pixels[y * width + x + 3];

			inputBlock[4] = pixels[(y + 1) * width + x];
			inputBlock[5] = pixels[(y + 1) * width + x + 1];
			inputBlock[6] = pixels[(y + 1) * width + x + 2];
			inputBlock[7] = pixels[(y + 1) * width + x + 3];

			inputBlock[8] = pixels[(y + 2) * width + x];
			inputBlock[9] = pixels[(y + 2) * width + x + 1];
			inputBlock[10] = pixels[(y + 2) * width + x + 2];
			inputBlock[11] = pixels[(y + 3) * width + x + 3];

			inputBlock[12] = pixels[(y + 3) * width + x];
			inputBlock[13] = pixels[(y + 3) * width + x + 1];
			inputBlock[14] = pixels[(y + 3) * width + x + 2];
			inputBlock[15] = pixels[(y + 3) * width + x + 3];

			const int by = y / 4;
			const int bx = x / 4;

			rgbcx::encode_bc4(&blocks[by * blocksX + bx], (const unsigned char*)&inputBlock, 1);
		}
	}
}

Array<unsigned char> S3TC::BC4(const Ref<Image>& image) {
	Array<unsigned char> compressedPixels((image->GetInfo().GetWidth() * image->GetInfo().GetHeight()) / 2);
	BC4(image->GetData().GetData(), image->GetData().GetSizeInBytes(), image->GetInfo().GetWidth(), compressedPixels.GetData());
	return compressedPixels;
}
