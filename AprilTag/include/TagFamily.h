#ifndef TAGFAMILY_H
#define TAGFAMILY_H

#include <climits>
#include <cmath>
#include <stdio.h>
#include <vector>
#include <map>

#include "TagDetection.h"
using namespace std;

#ifdef WIN32
#define _EXPORT_ __declspec(dllexport)
#else
#define _EXPORT_ __attribute__((visibility("default")))
#endif

namespace AprilTags {

class TagCodes {
public:
  int bits;
  int minHammingDistance;
  std::vector<unsigned long long> codes;
public:
 TagCodes(int bits, int minHammingDistance,
          const unsigned long long* codesA, int num)
   : bits(bits), minHammingDistance(minHammingDistance),
    codes(codesA, codesA+num) // created vector for all entries of codesA
      {}
};

//tag_36_11
const unsigned long long t36h11[] =
  { 0xd5d628584LL, 0xd97f18b49LL, 0xdd280910eLL, 0xe479e9c98LL, 0xebcbca822LL, 0xf31dab3acLL, 0x056a5d085LL, 0x10652e1d4LL, 0x22b1dfeadLL, 0x265ad0472LL, 0x34fe91b86LL, 0x3ff962cd5LL, 0x43a25329aLL, 0x474b4385fLL, 0x4e9d243e9LL, 0x5246149aeLL, 0x5997f5538LL, 0x683bb6c4cLL, 0x6be4a7211LL, 0x7e3158eeaLL, 0x81da494afLL, 0x858339a74LL, 0x8cd51a5feLL, 0x9f21cc2d7LL, 0xa2cabc89cLL, 0xadc58d9ebLL, 0xb16e7dfb0LL, 0xb8c05eb3aLL, 0xd25ef139dLL, 0xd607e1962LL, 0xe4aba3076LL, 0x2dde6a3daLL, 0x43d40c678LL, 0x5620be351LL, 0x64c47fa65LL, 0x686d7002aLL, 0x6c16605efLL, 0x6fbf50bb4LL, 0x8d06d39dcLL, 0x9f53856b5LL, 0xadf746dc9LL, 0xbc9b084ddLL, 0xd290aa77bLL, 0xd9e28b305LL, 0xe4dd5c454LL, 0xfad2fe6f2LL, 0x181a8151aLL, 0x26be42c2eLL, 0x2e10237b8LL, 0x405cd5491LL, 0x7742eab1cLL, 0x85e6ac230LL, 0x8d388cdbaLL, 0x9f853ea93LL, 0xc41ea2445LL, 0xcf1973594LL, 0x14a34a333LL, 0x31eacd15bLL, 0x6c79d2dabLL, 0x73cbb3935LL, 0x89c155bd3LL, 0x8d6a46198LL, 0x91133675dLL, 0xa708d89fbLL, 0xae5ab9585LL, 0xb9558a6d4LL, 0xb98743ab2LL, 0xd6cec68daLL, 0x1506bcaefLL, 0x4becd217aLL, 0x4f95c273fLL, 0x658b649ddLL, 0xa76c4b1b7LL, 0xecf621f56LL, 0x1c8a56a57LL, 0x3628e92baLL, 0x53706c0e2LL, 0x5e6b3d231LL, 0x7809cfa94LL, 0xe97eead6fLL, 0x5af40604aLL, 0x7492988adLL, 0xed5994712LL, 0x5eceaf9edLL, 0x7c1632815LL, 0xc1a0095b4LL, 0xe9e25d52bLL, 0x3a6705419LL, 0xa8333012fLL, 0x4ce5704d0LL, 0x508e60a95LL, 0x877476120LL, 0xa864e950dLL, 0xea45cfce7LL, 0x19da047e8LL, 0x24d4d5937LL, 0x6e079cc9bLL, 0x99f2e11d7LL, 0x33aa50429LL, 0x499ff26c7LL, 0x50f1d3251LL, 0x66e7754efLL, 0x96ad633ceLL, 0x9a5653993LL, 0xaca30566cLL, 0xc298a790aLL, 0x8be44b65dLL, 0xdc68f354bLL, 0x16f7f919bLL, 0x4dde0e826LL, 0xd548cbd9fLL, 0xe0439ceeeLL, 0xfd8b1fd16LL, 0x76521bb7bLL, 0xd92375742LL, 0xcab16d40cLL, 0x730c9dd72LL, 0xad9ba39c2LL, 0xb14493f87LL, 0x52b15651fLL, 0x185409cadLL, 0x77ae2c68dLL, 0x94f5af4b5LL, 0x0a13bad55LL, 0x61ea437cdLL, 0xa022399e2LL, 0x203b163d1LL, 0x7bba8f40eLL, 0x95bc9442dLL, 0x41c0b5358LL, 0x8e9c6cc81LL, 0x0eb549670LL, 0x9da3a0b51LL, 0xd832a67a1LL, 0xdcd4350bcLL, 0x4aa05fdd2LL, 0x60c7bb44eLL, 0x4b358b96cLL, 0x067299b45LL, 0xb9c89b5faLL, 0x6975acaeaLL, 0x62b8f7afaLL, 0x33567c3d7LL, 0xbac139950LL, 0xa5927c62aLL, 0x5c916e6a4LL, 0x260ecb7d5LL, 0x29b7bbd9aLL, 0x903205f26LL, 0xae72270a4LL, 0x3d2ec51a7LL, 0x82ea55324LL, 0x11a6f3427LL, 0x1ca1c4576LL, 0xa40c81aefLL, 0xbddccd730LL, 0x0e617561eLL, 0x969317b0fLL, 0x67f781364LL, 0x610912f96LL, 0xb2549fdfcLL, 0x06e5aaa6bLL, 0xb6c475339LL, 0xc56836a4dLL, 0x844e351ebLL, 0x4647f83b4LL, 0x0908a04f5LL, 0x7f51034c9LL, 0xaee537fcaLL, 0x5e92494baLL, 0xd445808f4LL, 0x28d68b563LL, 0x04d25374bLL, 0x2bc065f65LL, 0x96dc3ea0cLL, 0x4b2ade817LL, 0x07c3fd502LL, 0xe768b5cafLL, 0x17605cf6cLL, 0x182741ee4LL, 0x62846097cLL, 0x72b5ebf80LL, 0x263da6e13LL, 0xfa841bcb5LL, 0x7e45e8c69LL, 0x653c81fa0LL, 0x7443b5e70LL, 0x0a5234afdLL, 0x74756f24eLL, 0x157ebf02aLL, 0x82ef46939LL, 0x80d420264LL, 0x2aeed3e98LL, 0xb0a1dd4f8LL, 0xb5436be13LL, 0x7b7b4b13bLL, 0x1ce80d6d3LL, 0x16c08427dLL, 0xee54462ddLL, 0x1f7644cceLL, 0x9c7b5cc92LL, 0xe369138f8LL, 0x5d5a66e91LL, 0x485d62f49LL, 0xe6e819e94LL, 0xb1f340eb5LL, 0x09d198ce2LL, 0xd60717437LL, 0x0196b856cLL, 0xf0a6173a5LL, 0x12c0e1ec6LL, 0x62b82d5cfLL, 0xad154c067LL, 0xce3778832LL, 0x6b0a7b864LL, 0x4c7686694LL, 0x5058ff3ecLL, 0xd5e21ea23LL, 0x9ff4a76eeLL, 0x9dd981019LL, 0x1bad4d30aLL, 0xc601896d1LL, 0x973439b48LL, 0x1ce7431a8LL, 0x57a8021d6LL, 0xf9dba96e6LL, 0x83a2e4e7cLL, 0x8ea585380LL, 0xaf6c0e744LL, 0x875b73babLL, 0xda34ca901LL, 0x2ab9727efLL, 0xd39f21b9aLL, 0x8a10b742fLL, 0x5f8952dbaLL, 0xf8da71ab0LL, 0xc25f9df96LL, 0x06f8a5d94LL, 0xe42e63e1aLL, 0xb78409d1bLL, 0x792229addLL, 0x5acf8c455LL, 0x2fc29a9b0LL, 0xea486237bLL, 0xb0c9685a0LL, 0x1ad748a47LL, 0x03b4712d5LL, 0xf29216d30LL, 0x8dad65e49LL, 0x0a2cf09ddLL, 0x0b5f174c6LL, 0xe54f57743LL, 0xb9cf54d78LL, 0x4a312a88aLL, 0x27babc962LL, 0xb86897111LL, 0xf2ff6c116LL, 0x82274bd8aLL, 0x97023505eLL, 0x52d46edd1LL, 0x585c1f538LL, 0xbddd00e43LL, 0x5590b74dfLL, 0x729404a1fLL, 0x65320855eLL, 0xd3d4b6956LL, 0x7ae374f14LL, 0x2d7a60e06LL, 0x315cd9b5eLL, 0xfd36b4eacLL, 0xf1df7642bLL, 0x55db27726LL, 0x8f15ebc19LL, 0x992f8c531LL, 0x62dea2a40LL, 0x928275cabLL, 0x69c263cb9LL, 0xa774cca9eLL, 0x266b2110eLL, 0x1b14acbb8LL, 0x624b8a71bLL, 0x1c539406bLL, 0x3086d529bLL, 0x0111dd66eLL, 0x98cd630bfLL, 0x8b9d1ffdcLL, 0x72b2f61e7LL, 0x9ed9d672bLL, 0x96cdd15f3LL, 0x6366c2504LL, 0x6ca9df73aLL, 0xa066d60f0LL, 0xe7a4b8addLL, 0x8264647efLL, 0xaa195bf81LL, 0x9a3db8244LL, 0x014d2df6aLL, 0x0b63265b7LL, 0x2f010de73LL, 0x97e774986LL, 0x248affc29LL, 0xfb57dcd11LL, 0x0b1a7e4d9LL, 0x4bfa2d07dLL, 0x54e5cdf96LL, 0x4c15c1c86LL, 0xcd9c61166LL, 0x499380b2aLL, 0x540308d09LL, 0x8b63fe66fLL, 0xc81aeb35eLL, 0x86fe0bd5cLL, 0xce2480c2aLL, 0x1ab29ee60LL, 0x8048daa15LL, 0xdbfeb2d39LL, 0x567c9858cLL, 0x2b6edc5bcLL, 0x2078fca82LL, 0xadacc22aaLL, 0xb92486f49LL, 0x51fac5964LL, 0x691ee6420LL, 0xf63b3e129LL, 0x39be7e572LL, 0xda2ce6c74LL, 0x20cf17a5cLL, 0xee55f9b6eLL, 0xfb8572726LL, 0xb2c2de548LL, 0xcaa9bce92LL, 0xae9182db3LL, 0x74b6e5bd1LL, 0x137b252afLL, 0x51f686881LL, 0xd672f6c02LL, 0x654146ce4LL, 0xf944bc825LL, 0xe8327f809LL, 0x76a73fd59LL, 0xf79da4cb4LL, 0x956f8099bLL, 0x7b5f2655cLL, 0xd06b114a6LL, 0xd0697ca50LL, 0x27c390797LL, 0xbc61ed9b2LL, 0xcc12dd19bLL, 0xeb7818d2cLL, 0x092fcecdaLL, 0x89ded4ea1LL, 0x256a0ba34LL, 0xb6948e627LL, 0x1ef6b1054LL, 0x8639294a2LL, 0xeda3780a4LL, 0x39ee2af1dLL, 0xcd257edc5LL, 0x2d9d6bc22LL, 0x121d3b47dLL, 0x37e23f8adLL, 0x119f31cf6LL, 0x2c97f4f09LL, 0xd502abfe0LL, 0x10bc3ca77LL, 0x53d7190efLL, 0x90c3e62a6LL, 0x7e9ebf675LL, 0x979ce23d1LL, 0x27f0c98e9LL, 0xeafb4ae59LL, 0x7ca7fe2bdLL, 0x1490ca8f6LL, 0x9123387baLL, 0xb3bc73888LL, 0x3ea87e325LL, 0x4888964aaLL, 0xa0188a6b9LL, 0xcd383c666LL, 0x40029a3fdLL, 0xe1c00ac5cLL, 0x39e6f2b6eLL, 0xde664f622LL, 0xe979a75e8LL, 0x7c6b4c86cLL, 0xfd492e071LL, 0x8fbb35118LL, 0x40b4a09b7LL, 0xaf80bd6daLL, 0x70e0b2521LL, 0x2f5c54d93LL, 0x3f4a118d5LL, 0x09c1897b9LL, 0x079776eacLL, 0x084b00b17LL, 0x3a95ad90eLL, 0x28c544095LL, 0x39d457c05LL, 0x7a3791a78LL, 0xbb770e22eLL, 0x9a822bd6cLL, 0x68a4b1fedLL, 0xa5fd27b3bLL, 0x0c3995b79LL, 0xd1519dff1LL, 0x8e7eee359LL, 0xcd3ca50b1LL, 0xb73b8b793LL, 0x57aca1c43LL, 0xec2655277LL, 0x785a2c1b3LL, 0x75a07985aLL, 0xa4b01eb69LL, 0xa18a11347LL, 0xdb1f28ca3LL, 0x877ec3e25LL, 0x31f6341b8LL, 0x1363a3a4cLL, 0x075d8b9baLL, 0x7ae0792a9LL, 0xa83a21651LL, 0x7f08f9fb5LL, 0x0d0cf73a9LL, 0xb04dcc98eLL, 0xf65c7b0f8LL, 0x65ddaf69aLL, 0x2cf9b86b3LL, 0x14cb51e25LL, 0xf48027b5bLL, 0x0ec26ea8bLL, 0x44bafd45cLL, 0xb12c7c0c4LL, 0x959fd9d82LL, 0xc77c9725aLL, 0x48a22d462LL, 0x8398e8072LL, 0xec89b05ceLL, 0xbb682d4c9LL, 0xe5a86d2ffLL, 0x358f01134LL, 0x8556ddcf6LL, 0x67584b6e2LL, 0x11609439fLL, 0x08488816eLL, 0xaaf1a2c46LL, 0xf879898cfLL, 0x8bbe5e2f7LL, 0x101eee363LL, 0x690f69377LL, 0xf5bd93cd9LL, 0xcea4c2bf6LL, 0x9550be706LL, 0x2c5b38a60LL, 0xe72033547LL, 0x4458b0629LL, 0xee8d9ed41LL, 0xd2f918d72LL, 0x78dc39fd3LL, 0x8212636f6LL, 0x7450a72a7LL, 0xc4f0cf4c6LL, 0x367bcddcdLL, 0xc1caf8cc6LL, 0xa7f5b853dLL, 0x9d536818bLL, 0x535e021b0LL, 0xa7eb8729eLL, 0x422a67b49LL, 0x929e928a6LL, 0x48e8aefccLL, 0xa9897393cLL, 0x5eb81d37eLL, 0x1e80287b7LL, 0x34770d903LL, 0x2eef86728LL, 0x59266ccb6LL, 0x0110bba61LL, 0x1dfd284efLL, 0x447439d1bLL, 0xfece0e599LL, 0x9309f3703LL, 0x80764d1ddLL, 0x353f1e6a0LL, 0x2c1c12dccLL, 0xc1d21b9d7LL, 0x457ee453eLL, 0xd66faf540LL, 0x44831e652LL, 0xcfd49a848LL, 0x9312d4133LL, 0x3f097d3eeLL, 0x8c9ebef7aLL, 0xa99e29e88LL, 0x0e9fab22cLL, 0x4e748f4fbLL, 0xecdee4288LL, 0xabce5f1d0LL, 0xc42f6876cLL, 0x7ed402ea0LL, 0xe5c4242c3LL, 0xd5b2c31aeLL, 0x286863be6LL, 0x160444d94LL, 0x5f0f5808eLL, 0xae3d44b2aLL, 0x9f5c5d109LL, 0x8ad9316d7LL, 0x3422ba064LL, 0x2fed11d56LL, 0xbea6e3e04LL, 0x04b029eecLL, 0x6deed7435LL, 0x3718ce17cLL, 0x55857f5e2LL, 0x2edac7b62LL, 0x085d6c512LL, 0xd6ca88e0fLL, 0x2b7e1fc69LL, 0xa699d5c1bLL, 0xf05ad74deLL, 0x4cf5fb56dLL, 0x5725e07e1LL, 0x72f18a2deLL, 0x1cec52609LL, 0x48534243cLL, 0x2523a4d69LL, 0x35c1b80d1LL, 0xa4d7338a7LL, 0x0db1af012LL, 0xe61a9475dLL, 0x05df03f91LL, 0x97ae260bbLL, 0x32d627fefLL, 0xb640f73c2LL, 0x45a1ac9c6LL, 0x6a2202de1LL, 0x57d3e25f2LL, 0x5aa9f986eLL, 0x0cc859d8aLL, 0xe3ec6cca8LL, 0x54e95e1aeLL, 0x446887b06LL, 0x7516732beLL, 0x3817ac8f5LL, 0x3e26d938cLL, 0xaa81bc235LL, 0xdf387ca1bLL, 0x0f3a3b3f2LL, 0xb4bf69677LL, 0xae21868edLL, 0x81e1d2d9dLL, 0xa0a9ea14cLL, 0x8eee297a9LL, 0x4740c0559LL, 0xe8b141837LL, 0xac69e0a3dLL, 0x9ed83a1e1LL, 0x5edb55ecbLL, 0x07340fe81LL, 0x50dfbc6bfLL, 0x4f583508aLL, 0xcb1fb78bcLL, 0x4025ced2fLL, 0x39791ebecLL, 0x53ee388f1LL, 0x7d6c0bd23LL, 0x93a995fbeLL, 0x8a41728deLL, 0x2fe70e053LL, 0xab3db443aLL, 0x1364edb05LL, 0x47b6eeed6LL, 0x12e71af01LL, 0x52ff83587LL, 0x3a1575dd8LL, 0x3feaa3564LL, 0xeacf78ba7LL, 0x0872b94f8LL, 0xda8ddf9a2LL, 0x9aa920d2bLL, 0x1f350ed36LL, 0x18a5e861fLL, 0x2c35b89c3LL, 0x3347ac48aLL, 0x7f23e022eLL, 0x2459068fbLL, 0xe83be4b73LL };
static const TagCodes tagCodes36h11 = TagCodes(36, 11, t36h11, sizeof(t36h11)/sizeof(t36h11[0]));

//tag_16_05
const unsigned long long t16h5[] =
		{ 0x231bLL, 0x2ea5LL, 0x346aLL, 0x45b9LL, 0x79a6LL, 0x7f6bLL, 0xb358LL, 0xe745LL, 0xfe59LL, 0x156dLL, 0x380bLL, 0xf0abLL, 0x0d84LL, 0x4736LL, 0x8c72LL, 0xaf10LL, 0x093cLL, 0x93b4LL, 0xa503LL, 0x468fLL, 0xe137LL, 0x5795LL, 0xdf42LL, 0x1c1dLL, 0xe9dcLL, 0x73adLL, 0xad5fLL, 0xd530LL, 0x07caLL, 0xaf2eLL };
static const TagCodes tagCodes16h5 = TagCodes(16, 5, t16h5, sizeof(t16h5)/sizeof(t16h5[0]));


//! Generic class for all tag encoding families
class _EXPORT_ TagFamily {
public:
  //! The codes array is not copied internally and so must not be modified externally.
  TagFamily(const TagCodes& tagCodes, const size_t blackBorder);

  void setErrorRecoveryBits(int b);

  void setErrorRecoveryFraction(float v);

  /* if the bits in w were arranged in a d*d grid and that grid was
   * rotated, what would the new bits in w be?
   * The bits are organized like this (for d = 3):
   *
   *  8 7 6       2 5 8      0 1 2
   *  5 4 3  ==>  1 4 7 ==>  3 4 5    (rotate90 applied twice)
   *  2 1 0       0 3 6      6 7 8
   */
  static unsigned long long rotate90(unsigned long long w, int d);

  //! Computes the hamming distance between two unsigned long longs.
  static int hammingDistance(unsigned long long a, unsigned long long b);

  //! How many bits are set in the unsigned long long?
  static unsigned char popCountReal(unsigned long long w);

  static int popCount(unsigned long long w);

  //! Given an observed tag with code 'rCode', try to recover the id.
  /*  The corresponding fields of TagDetection will be filled in. */
  void decode(TagDetection& det, unsigned long long rCode) const;

  //! Prints the hamming distances of the tag codes.
  void printHammingDistances() const;

  //! Numer of pixels wide of the inner black border.
  int blackBorder;

  //! Number of bits in the tag. Must be n^2.
  int bits;

  //! Dimension of tag. e.g. for 16 bits, dimension=4. Must be sqrt(bits).
  int dimension;

  //! Minimum hamming distance between any two codes.
  /*  Accounting for rotational ambiguity? The code can recover
   *  (minHammingDistance-1)/2 bit errors.
   */
  int minimumHammingDistance;

  /* The error recovery value determines our position on the ROC
   * curve. We will report codes that are within errorRecoveryBits
   * of a valid code. Small values mean greater rejection of bogus
   * tags (but false negatives). Large values mean aggressive
   * reporting of bad tags (but with a corresponding increase in
   * false positives).
   */
  int errorRecoveryBits;

  //! The array of the codes. The id for a code is its index.
  std::vector<unsigned long long> codes;

  static const int  popCountTableShift = 12;
  static const unsigned int popCountTableSize = 1 << popCountTableShift;
  static unsigned char popCountTable[popCountTableSize];

  //! Initializes the static popCountTable
  static class TableInitializer {
  public:
    TableInitializer() {
      for (unsigned int i = 0; i < TagFamily::popCountTableSize; i++)
        TagFamily::popCountTable[i] = TagFamily::popCountReal(i);
    }
  } initializer;
};

} // namespace

#endif
