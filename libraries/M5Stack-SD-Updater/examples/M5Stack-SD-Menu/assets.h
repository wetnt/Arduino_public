
/*
 * Image Source: https://i.imgur.com/llemDHF.gif
 * 
 * - ImageMagick:
 *    #> convert -strip disk.gif disk%02d.jpg
 * 
 * - Crop visual to 30x30 in an image editor
 * 
 * - Export to C uchar format:
 *    #> xxd -i disk00.jpg >> assets.h
 *    #> xxd -i disk01.jpg >> assets.h
 * 
 * 
 */

unsigned char disk00_jpg[1775] = {
  0xff, 0xd8, 0xff, 0xe0, 0x00, 0x10, 0x4a, 0x46, 0x49, 0x46, 0x00, 0x01,
  0x01, 0x01, 0x00, 0x60, 0x00, 0x60, 0x00, 0x00, 0xff, 0xdb, 0x00, 0x43,
  0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 0xdb, 0x00, 0x43, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0xff, 0xc0, 0x00, 0x11, 0x08, 0x00, 0x1e, 0x00, 0x1e, 0x03,
  0x01, 0x22, 0x00, 0x02, 0x11, 0x01, 0x03, 0x11, 0x01, 0xff, 0xc4, 0x00,
  0x1f, 0x00, 0x00, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
  0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0xff, 0xc4, 0x00, 0xb5, 0x10, 0x00,
  0x02, 0x01, 0x03, 0x03, 0x02, 0x04, 0x03, 0x05, 0x05, 0x04, 0x04, 0x00,
  0x00, 0x01, 0x7d, 0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12, 0x21,
  0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07, 0x22, 0x71, 0x14, 0x32, 0x81,
  0x91, 0xa1, 0x08, 0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0, 0x24,
  0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x25,
  0x26, 0x27, 0x28, 0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a,
  0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x53, 0x54, 0x55, 0x56,
  0x57, 0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a,
  0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x83, 0x84, 0x85, 0x86,
  0x87, 0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99,
  0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3,
  0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6,
  0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9,
  0xda, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xf1,
  0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xff, 0xc4, 0x00,
  0x1f, 0x01, 0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
  0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0xff, 0xc4, 0x00, 0xb5, 0x11, 0x00,
  0x02, 0x01, 0x02, 0x04, 0x04, 0x03, 0x04, 0x07, 0x05, 0x04, 0x04, 0x00,
  0x01, 0x02, 0x77, 0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21, 0x31,
  0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71, 0x13, 0x22, 0x32, 0x81, 0x08,
  0x14, 0x42, 0x91, 0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0, 0x15,
  0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34, 0xe1, 0x25, 0xf1, 0x17, 0x18,
  0x19, 0x1a, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38, 0x39,
  0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x53, 0x54, 0x55,
  0x56, 0x57, 0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
  0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x82, 0x83, 0x84,
  0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
  0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa,
  0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4,
  0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
  0xd8, 0xd9, 0xda, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
  0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xff, 0xda, 0x00,
  0x0c, 0x03, 0x01, 0x00, 0x02, 0x11, 0x03, 0x11, 0x00, 0x3f, 0x00, 0xfe,
  0xc7, 0x7f, 0x6f, 0xc0, 0x7f, 0xe1, 0x45, 0x78, 0x04, 0x16, 0x04, 0xaf,
  0xed, 0xaf, 0xff, 0x00, 0x04, 0xd4, 0x0d, 0xb7, 0x20, 0x93, 0xff, 0x00,
  0x0f, 0x16, 0xfd, 0x95, 0xf2, 0x06, 0x64, 0x24, 0x65, 0x8a, 0xb9, 0x0e,
  0x64, 0x25, 0x41, 0x03, 0x2c, 0x55, 0xc7, 0xa9, 0xfe, 0xd7, 0x7a, 0xff,
  0x00, 0xc5, 0x4f, 0x09, 0xfe, 0xc9, 0xff, 0x00, 0xb4, 0xff, 0x00, 0x8a,
  0xbe, 0x05, 0x43, 0xad, 0xdc, 0xfc, 0x6f, 0xf0, 0xcf, 0xec, 0xf1, 0xf1,
  0xab, 0xc4, 0x1f, 0x07, 0x2d, 0xfc, 0x37, 0xe1, 0xa8, 0xfc, 0x6d, 0xe2,
  0x29, 0xfe, 0x2a, 0xe8, 0xdf, 0x0d, 0xbc, 0x4b, 0xa8, 0xfc, 0x3d, 0x87,
  0x40, 0xf0, 0x64, 0xfa, 0x66, 0xb7, 0x07, 0x8b, 0xb5, 0xa9, 0x7c, 0x5d,
  0x6d, 0xa4, 0x26, 0x97, 0xe1, 0x89, 0xb4, 0x5d, 0x5e, 0x2d, 0x7e, 0xf9,
  0xa0, 0xd2, 0xa4, 0xd2, 0xef, 0xd2, 0xec, 0xda, 0x4b, 0xe4, 0xff, 0x00,
  0xb4, 0xaf, 0xc5, 0x3f, 0x0c, 0xeb, 0xba, 0xb6, 0xbb, 0xfb, 0x33, 0xc7,
  0xfb, 0x34, 0xfc, 0x6c, 0xfd, 0xaa, 0x35, 0xcf, 0xf8, 0x42, 0xbc, 0x0f,
  0xf1, 0x2f, 0xe2, 0x27, 0x86, 0x3e, 0x0c, 0x6b, 0xff, 0x00, 0x07, 0xbc,
  0x0d, 0xaa, 0x7c, 0x2a, 0xd0, 0xbc, 0x4b, 0xe3, 0x2f, 0x14, 0xc5, 0xf0,
  0x4b, 0xc7, 0xb0, 0xf8, 0xf3, 0xe3, 0x37, 0xc7, 0xdf, 0xd9, 0xda, 0xeb,
  0x43, 0xf1, 0x9d, 0xd7, 0xc4, 0x0f, 0x83, 0x1e, 0x39, 0xf1, 0x17, 0xc2,
  0xef, 0x15, 0xfc, 0x12, 0xf1, 0x4e, 0xa7, 0xf1, 0x1b, 0xe1, 0x6f, 0x8d,
  0x7e, 0x13, 0x58, 0xf8, 0xde, 0xe2, 0xf3, 0xe1, 0xb6, 0xb3, 0x27, 0xc3,
  0x6d, 0x6f, 0x5d, 0xf8, 0xbc, 0xfc, 0x2c, 0x18, 0xc0, 0xfd, 0x84, 0x7f,
  0xe0, 0xb5, 0xb9, 0x20, 0x95, 0xcf, 0xfc, 0x15, 0x95, 0x1b, 0x3d, 0x00,
  0x3b, 0x5f, 0xfe, 0x0b, 0x48, 0xe8, 0xc3, 0x25, 0x78, 0x64, 0x64, 0x39,
  0x01, 0x95, 0x81, 0xc1, 0x00, 0xf2, 0x9f, 0x12, 0x78, 0xbb, 0xc0, 0x1a,
  0xdd, 0xa7, 0xc4, 0xaf, 0x0f, 0xfe, 0xce, 0x5f, 0x1a, 0xf5, 0xbf, 0x8f,
  0xbf, 0xb2, 0x8e, 0x83, 0xfb, 0x43, 0xff, 0x00, 0xc1, 0x12, 0xb5, 0x9f,
  0x0a, 0x78, 0xe6, 0x6f, 0xda, 0x27, 0xc6, 0xdf, 0xb5, 0x9f, 0x87, 0x2c,
  0xbf, 0x68, 0x5f, 0x12, 0xff, 0x00, 0xc1, 0x50, 0xb4, 0xab, 0x2f, 0x8e,
  0x3e, 0x0e, 0xd2, 0xbe, 0x3f, 0x78, 0xf7, 0xc7, 0xbf, 0x16, 0x3c, 0x48,
  0x75, 0x8d, 0x1f, 0xe1, 0xb7, 0x85, 0xff, 0x00, 0x66, 0x6d, 0x6b, 0x5e,
  0xf8, 0x41, 0x0f, 0xc4, 0x09, 0x74, 0x8f, 0x00, 0xd8, 0xf8, 0x8b, 0xc3,
  0x3e, 0x30, 0xd3, 0xfc, 0x1f, 0xe1, 0xeb, 0x8f, 0x8b, 0x5a, 0xae, 0xb5,
  0xe3, 0x5f, 0xaf, 0x3f, 0xe0, 0xa2, 0x9f, 0xf0, 0x48, 0x7f, 0xd9, 0x0b,
  0xfe, 0x0a, 0x6e, 0xde, 0x04, 0xd5, 0x7e, 0x3d, 0x69, 0xbe, 0x33, 0xf0,
  0x9f, 0xc4, 0x1f, 0x87, 0x62, 0x5d, 0x3b, 0x42, 0xf8, 0xb3, 0xf0, 0x87,
  0x51, 0xf0, 0xaf, 0x86, 0xfe, 0x21, 0xde, 0x78, 0x36, 0x56, 0xd4, 0xee,
  0x26, 0xf8, 0x73, 0xe2, 0x3d, 0x43, 0xc5, 0x9e, 0x0b, 0xf1, 0xe6, 0x87,
  0xe2, 0x2f, 0x06, 0xdb, 0xeb, 0x9a, 0x94, 0x9e, 0x24, 0xd2, 0x2d, 0x35,
  0x6f, 0x0f, 0xdc, 0xea, 0xbe, 0x17, 0xd7, 0x24, 0xd5, 0x6e, 0x7c, 0x17,
  0xad, 0x78, 0x7a, 0xcb, 0xc6, 0x3e, 0x3f, 0xb0, 0xf1, 0x57, 0x98, 0x78,
  0x6f, 0xc0, 0xb0, 0x78, 0x6b, 0xc4, 0x9e, 0x1f, 0xf1, 0x29, 0xff, 0x00,
  0x82, 0x71, 0xff, 0x00, 0xc1, 0x56, 0xfc, 0x79, 0x71, 0xe1, 0xbd, 0x63,
  0x4a, 0xf1, 0x36, 0x8f, 0xa0, 0xfc, 0x61, 0xff, 0x00, 0x82, 0x82, 0xfc,
  0x2a, 0xf8, 0xed, 0xf0, 0xfe, 0x3f, 0x10, 0xe8, 0x57, 0xf1, 0xeb, 0x7e,
  0x17, 0xf1, 0x0e, 0xa1, 0xf0, 0xc3, 0xe3, 0x5f, 0xfc, 0x15, 0xcf, 0xc7,
  0xbf, 0x0e, 0x35, 0x6d, 0x73, 0xc2, 0x3e, 0x23, 0xb0, 0xd3, 0x7c, 0x5b,
  0xe0, 0xad, 0x73, 0x57, 0xf0, 0xa6, 0xa3, 0xa9, 0x78, 0x3b, 0xc6, 0x9a,
  0x2f, 0x87, 0xfc, 0x69, 0xe1, 0x7b, 0x8d, 0x27, 0xc5, 0xbe, 0x1c, 0xd0,
  0xf5, 0xad, 0x3f, 0xf4, 0x97, 0xe0, 0x6f, 0xc6, 0xdd, 0x33, 0xe3, 0x5e,
  0x99, 0xe3, 0x5f, 0xf8, 0xa3, 0x3c, 0x71, 0xf0, 0xd3, 0xc6, 0x7f, 0x0c,
  0x7c, 0x70, 0xdf, 0x0e, 0xbe, 0x28, 0xfc, 0x2e, 0xf8, 0x88, 0x3c, 0x1f,
  0x37, 0x8b, 0xfe, 0x1e, 0xf8, 0xce, 0x6f, 0x07, 0xf8, 0x3f, 0xe2, 0x46,
  0x91, 0xa3, 0xea, 0x9a, 0xb7, 0xc3, 0x6f, 0x1a, 0x7c, 0x46, 0xf8, 0x6f,
  0xad, 0x26, 0xbd, 0xf0, 0xc7, 0xe2, 0x27, 0xc3, 0xcf, 0x88, 0x1a, 0x75,
  0xe7, 0x81, 0xbe, 0x20, 0x78, 0xbf, 0x4a, 0xb3, 0xd2, 0x7c, 0x69, 0xa7,
  0xe8, 0x7a, 0xce, 0xa1, 0xa4, 0x78, 0xdb, 0x47, 0xf1, 0x67, 0x84, 0xbc,
  0x36, 0x01, 0xe3, 0x5e, 0x06, 0xe3, 0xfe, 0x0a, 0x2f, 0xfb, 0x56, 0x31,
  0x19, 0x51, 0xfb, 0x13, 0x7e, 0xc0, 0x60, 0xe7, 0x1b, 0x49, 0x5f, 0x8e,
  0x7f, 0xf0, 0x52, 0xb6, 0x65, 0x25, 0x8a, 0xae, 0x42, 0xb2, 0x92, 0x0b,
  0x00, 0x03, 0x02, 0x48, 0x07, 0x35, 0xf9, 0xd9, 0xff, 0x00, 0x05, 0x69,
  0xfd, 0x8c, 0xff, 0x00, 0x63, 0x9d, 0x7f, 0xc5, 0x1e, 0x21, 0xff, 0x00,
  0x82, 0x87, 0x7f, 0xc1, 0x46, 0x3c, 0x4d, 0xe3, 0x6f, 0x89, 0xff, 0x00,
  0xb2, 0x37, 0xec, 0xd3, 0xfb, 0x2f, 0xb7, 0xc3, 0xad, 0x1f, 0xf6, 0x5b,
  0xf0, 0xf9, 0xf8, 0xa9, 0xa6, 0x3d, 0x87, 0xc6, 0x2f, 0x15, 0xfc, 0x65,
  0xd3, 0x6e, 0x2c, 0xbe, 0x2b, 0x78, 0x37, 0xc4, 0x7f, 0x0f, 0x7e, 0x2e,
  0x78, 0x2a, 0x41, 0xe3, 0x8f, 0x89, 0x4f, 0xab, 0x78, 0x3f, 0xe0, 0x9d,
  0xce, 0x83, 0xaa, 0x69, 0x7a, 0x2f, 0x85, 0xb5, 0x13, 0xff, 0x00, 0x08,
  0xbf, 0x8a, 0x7e, 0x22, 0x78, 0xfb, 0x4d, 0xf0, 0xe7, 0x83, 0xed, 0x2e,
  0xbc, 0x3d, 0xfa, 0x1f, 0xe0, 0x40, 0x47, 0xfc, 0x14, 0x5f, 0xf6, 0xa7,
  0x7c, 0x2e, 0x5b, 0xf6, 0x2a, 0xfd, 0x81, 0x11, 0x8e, 0x46, 0xe0, 0x63,
  0xf8, 0xe7, 0xff, 0x00, 0x05, 0x27, 0x3b, 0x72, 0x50, 0xef, 0x54, 0xcc,
  0x92, 0x46, 0xc7, 0x6b, 0x79, 0x8c, 0xc1, 0xbe, 0x56, 0x1e, 0x5f, 0x69,
  0xfb, 0x65, 0xfe, 0xcf, 0x9a, 0xe7, 0xed, 0x51, 0xfb, 0x37, 0xfc, 0x47,
  0xf8, 0x0b, 0xe1, 0x7f, 0x1a, 0xf8, 0x27, 0xe1, 0xbe, 0xb9, 0xe3, 0xa5,
  0xf0, 0x7a, 0xd9, 0xf8, 0xc7, 0xe2, 0x17, 0xc0, 0x7f, 0x87, 0x5f, 0xb4,
  0xc7, 0x83, 0xb4, 0x65, 0xf0, 0xaf, 0x8e, 0xfc, 0x27, 0xe3, 0x4b, 0x84,
  0xd5, 0x7e, 0x0a, 0x7c, 0x57, 0x56, 0xf0, 0x07, 0x8d, 0x45, 0xf5, 0xae,
  0x89, 0x3e, 0x97, 0xa6, 0xff, 0x00, 0xc2, 0x43, 0x13, 0x8f, 0x0d, 0x6a,
  0x77, 0xf6, 0xbe, 0x2b, 0xd2, 0x16, 0x3d, 0x6b, 0x42, 0xd3, 0x98, 0x80,
  0x7c, 0x1d, 0xff, 0x00, 0x04, 0x34, 0xfd, 0x9f, 0x7e, 0x34, 0x7e, 0xcf,
  0x1f, 0xb1, 0xa7, 0x88, 0xb4, 0xaf, 0x8b, 0xff, 0x00, 0x0e, 0x75, 0x8f,
  0x81, 0x3a, 0x17, 0xc5, 0x3f, 0xda, 0x1b, 0xe2, 0xb7, 0xc7, 0x2f, 0x80,
  0x5f, 0xb3, 0x3f, 0x89, 0x7e, 0x20, 0xf8, 0xaf, 0xe2, 0x27, 0x88, 0xff,
  0x00, 0x66, 0x1f, 0xd9, 0xf7, 0xe2, 0x52, 0xf8, 0x53, 0x50, 0xf0, 0x27,
  0xc1, 0x3d, 0x7a, 0xff, 0x00, 0xc6, 0x76, 0x36, 0x7a, 0x9e, 0x8d, 0xad,
  0x69, 0x3a, 0xbd, 0xaf, 0x8a, 0x3c, 0x57, 0xab, 0xe8, 0xb7, 0x09, 0x0e,
  0xbc, 0xda, 0x8f, 0x8b, 0xae, 0x35, 0xdf, 0x88, 0x1a, 0x6e, 0x83, 0xf1,
  0x6b, 0x5e, 0xf1, 0xef, 0x86, 0xb4, 0x2f, 0xb0, 0xbf, 0x65, 0x60, 0x47,
  0xc7, 0x5f, 0xf8, 0x29, 0x5e, 0x46, 0x33, 0xfb, 0x6b, 0xf8, 0x0d, 0x86,
  0x7b, 0xaf, 0xfc, 0x3b, 0x9b, 0xf6, 0x02, 0x5c, 0x8f, 0x51, 0xb9, 0x58,
  0x67, 0xa6, 0x54, 0x8e, 0xa0, 0xd7, 0xd9, 0xcb, 0x8c, 0x90, 0x15, 0x59,
  0xc3, 0x64, 0xfc, 0xa1, 0x14, 0xbf, 0xef, 0x21, 0xdc, 0x3f, 0xd6, 0x1f,
  0x98, 0x47, 0xe5, 0xf2, 0x58, 0xa4, 0x47, 0x0a, 0x71, 0xfb, 0xb1, 0xf1,
  0x67, 0xec, 0xae, 0xad, 0xff, 0x00, 0x0b, 0xcf, 0xfe, 0x0a, 0x50, 0x54,
  0x2e, 0xe9, 0x3f, 0x6d, 0x5f, 0x02, 0x49, 0xf7, 0xca, 0x64, 0x0f, 0xf8,
  0x27, 0x4f, 0xec, 0x0a, 0xa1, 0xdd, 0xd6, 0x32, 0x4c, 0x85, 0x42, 0x29,
  0x50, 0xbb, 0x02, 0x22, 0x00, 0x49, 0x52, 0xce, 0x01, 0xff, 0xd9
}; 

unsigned char disk01_jpg[1486] = {
  0xff, 0xd8, 0xff, 0xe0, 0x00, 0x10, 0x4a, 0x46, 0x49, 0x46, 0x00, 0x01,
  0x01, 0x01, 0x00, 0x60, 0x00, 0x60, 0x00, 0x00, 0xff, 0xdb, 0x00, 0x43,
  0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0xff, 0xdb, 0x00, 0x43, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x01, 0xff, 0xc0, 0x00, 0x11, 0x08, 0x00, 0x1e, 0x00, 0x1e, 0x03,
  0x01, 0x22, 0x00, 0x02, 0x11, 0x01, 0x03, 0x11, 0x01, 0xff, 0xc4, 0x00,
  0x1f, 0x00, 0x00, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
  0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0xff, 0xc4, 0x00, 0xb5, 0x10, 0x00,
  0x02, 0x01, 0x03, 0x03, 0x02, 0x04, 0x03, 0x05, 0x05, 0x04, 0x04, 0x00,
  0x00, 0x01, 0x7d, 0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12, 0x21,
  0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07, 0x22, 0x71, 0x14, 0x32, 0x81,
  0x91, 0xa1, 0x08, 0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0, 0x24,
  0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x25,
  0x26, 0x27, 0x28, 0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a,
  0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x53, 0x54, 0x55, 0x56,
  0x57, 0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a,
  0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x83, 0x84, 0x85, 0x86,
  0x87, 0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99,
  0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3,
  0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6,
  0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9,
  0xda, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xf1,
  0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xff, 0xc4, 0x00,
  0x1f, 0x01, 0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
  0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0xff, 0xc4, 0x00, 0xb5, 0x11, 0x00,
  0x02, 0x01, 0x02, 0x04, 0x04, 0x03, 0x04, 0x07, 0x05, 0x04, 0x04, 0x00,
  0x01, 0x02, 0x77, 0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21, 0x31,
  0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71, 0x13, 0x22, 0x32, 0x81, 0x08,
  0x14, 0x42, 0x91, 0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0, 0x15,
  0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34, 0xe1, 0x25, 0xf1, 0x17, 0x18,
  0x19, 0x1a, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38, 0x39,
  0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x53, 0x54, 0x55,
  0x56, 0x57, 0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
  0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x82, 0x83, 0x84,
  0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
  0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa,
  0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4,
  0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
  0xd8, 0xd9, 0xda, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
  0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xff, 0xda, 0x00,
  0x0c, 0x03, 0x01, 0x00, 0x02, 0x11, 0x03, 0x11, 0x00, 0x3f, 0x00, 0xfe,
  0xc7, 0x7f, 0x6f, 0xc0, 0x7f, 0xe1, 0x45, 0x78, 0x04, 0x16, 0x04, 0xaf,
  0xed, 0xaf, 0xff, 0x00, 0x04, 0xd4, 0x0d, 0xb7, 0x20, 0x93, 0xff, 0x00,
  0x0f, 0x16, 0xfd, 0x95, 0xf2, 0x06, 0x64, 0x24, 0x65, 0x8a, 0xb9, 0x0e,
  0x64, 0x25, 0x41, 0x03, 0x2c, 0x55, 0xc7, 0xa9, 0xfe, 0xd7, 0x7a, 0xff,
  0x00, 0xc5, 0x4f, 0x09, 0xfe, 0xc9, 0xff, 0x00, 0xb4, 0xff, 0x00, 0x8a,
  0xbe, 0x05, 0x43, 0xad, 0xdc, 0xfc, 0x6f, 0xf0, 0xcf, 0xec, 0xf1, 0xf1,
  0xab, 0xc4, 0x1f, 0x07, 0x2d, 0xfc, 0x37, 0xe1, 0xa8, 0xfc, 0x6d, 0xe2,
  0x29, 0xfe, 0x2a, 0xe8, 0xdf, 0x0d, 0xbc, 0x4b, 0xa8, 0xfc, 0x3d, 0x87,
  0x40, 0xf0, 0x64, 0xfa, 0x66, 0xb7, 0x07, 0x8b, 0xb5, 0xa9, 0x7c, 0x5d,
  0x6d, 0xa4, 0x26, 0x97, 0xe1, 0x89, 0xb4, 0x5d, 0x5e, 0x2d, 0x7e, 0xf9,
  0xa0, 0xd2, 0xa4, 0xd2, 0xef, 0xd2, 0xec, 0xda, 0x4b, 0xe4, 0xff, 0x00,
  0xb4, 0xaf, 0xc5, 0x3f, 0x0c, 0xeb, 0xba, 0xb6, 0xbb, 0xfb, 0x33, 0xc7,
  0xfb, 0x34, 0xfc, 0x6c, 0xfd, 0xaa, 0x35, 0xcf, 0xf8, 0x42, 0xbc, 0x0f,
  0xf1, 0x2f, 0xe2, 0x27, 0x86, 0x3e, 0x0c, 0x6b, 0xff, 0x00, 0x07, 0xbc,
  0x0d, 0xaa, 0x7c, 0x2a, 0xd0, 0xbc, 0x4b, 0xe3, 0x2f, 0x14, 0xc5, 0xf0,
  0x4b, 0xc7, 0xb0, 0xf8, 0xf3, 0xe3, 0x37, 0xc7, 0xdf, 0xd9, 0xda, 0xeb,
  0x43, 0xf1, 0x9d, 0xd7, 0xc4, 0x0f, 0x83, 0x1e, 0x39, 0xf1, 0x17, 0xc2,
  0xef, 0x15, 0xfc, 0x12, 0xf1, 0x4e, 0xa7, 0xf1, 0x1b, 0xe1, 0x6f, 0x8d,
  0x7e, 0x13, 0x58, 0xf8, 0xde, 0xe2, 0xf3, 0xe1, 0xb6, 0xb3, 0x27, 0xc3,
  0x6d, 0x6f, 0x5d, 0xf8, 0xc0, 0xfc, 0x2b, 0x38, 0x38, 0xfd, 0x84, 0x3f,
  0xe0, 0xb5, 0xd9, 0xc1, 0xc6, 0x7f, 0xe0, 0xac, 0x8a, 0xc3, 0x3d, 0xbe,
  0x57, 0xff, 0x00, 0x82, 0xd2, 0x3a, 0x37, 0xd1, 0xd1, 0x94, 0xf4, 0x65,
  0x61, 0x90, 0x40, 0x3c, 0xa3, 0xc4, 0x9e, 0x2e, 0xf0, 0x06, 0xb7, 0x69,
  0xf1, 0x2b, 0xc3, 0xff, 0x00, 0xb3, 0x97, 0xc6, 0xbd, 0x6f, 0xe3, 0xef,
  0xec, 0xa3, 0xa0, 0xfe, 0xd0, 0xff, 0x00, 0xf0, 0x44, 0xad, 0x67, 0xc2,
  0x9e, 0x39, 0x9b, 0xf6, 0x89, 0xf1, 0xb7, 0xed, 0x67, 0xe1, 0xcb, 0x2f,
  0xda, 0x17, 0xc4, 0xbf, 0xf0, 0x54, 0x2d, 0x2a, 0xcb, 0xe3, 0x8f, 0x83,
  0xb4, 0xaf, 0x8f, 0xde, 0x3d, 0xf1, 0xef, 0xc5, 0x8f, 0x12, 0x1d, 0x63,
  0x47, 0xf8, 0x6d, 0xe1, 0x7f, 0xd9, 0x9b, 0x5a, 0xd7, 0xbe, 0x10, 0x43,
  0xf1, 0x02, 0x5d, 0x23, 0xc0, 0x36, 0x3e, 0x22, 0xf0, 0xcf, 0x8c, 0x34,
  0xff, 0x00, 0x07, 0xf8, 0x7a, 0xe3, 0xe2, 0xd6, 0xab, 0xad, 0x78, 0xd7,
  0xeb, 0xcf, 0xf8, 0x28, 0xa7, 0xfc, 0x12, 0x1f, 0xf6, 0x42, 0xff, 0x00,
  0x82, 0x9b, 0xb7, 0x81, 0x35, 0x5f, 0x8f, 0x5a, 0x6f, 0x8c, 0xfc, 0x27,
  0xf1, 0x07, 0xe1, 0xd8, 0x97, 0x4e, 0xd0, 0xbe, 0x2c, 0xfc, 0x21, 0xd4,
  0x7c, 0x2b, 0xe1, 0xbf, 0x88, 0x77, 0x9e, 0x0d, 0x95, 0xb5, 0x3b, 0x89,
  0xbe, 0x1c, 0xf8, 0x8f, 0x50, 0xf1, 0x67, 0x82, 0xfc, 0x79, 0xa1, 0xf8,
  0x8b, 0xc1, 0xb6, 0xfa, 0xe6, 0xa5, 0x27, 0x89, 0x34, 0x8b, 0x4d, 0x5b,
  0xc3, 0xf7, 0x3a, 0xaf, 0x85, 0xf5, 0xc9, 0x35, 0x5b, 0x9f, 0x05, 0xeb,
  0x5e, 0x1e, 0xb2, 0xf1, 0x8f, 0x8f, 0xec, 0x3c, 0x55, 0xe6, 0x3e, 0x1c,
  0xf0, 0x1c, 0x5e, 0x18, 0xf1, 0x26, 0x81, 0xe2, 0x67, 0xff, 0x00, 0x82,
  0x70, 0xff, 0x00, 0xc1, 0x57, 0x3c, 0x75, 0x71, 0xe1, 0xad, 0x67, 0x4b,
  0xf1, 0x26, 0x8f, 0xa0, 0xfc, 0x62, 0xff, 0x00, 0x82, 0x82, 0x7c, 0x2b,
  0xf8, 0xeb, 0xf0, 0xfe, 0x3f, 0x11, 0xe8, 0x17, 0xf1, 0x6b, 0x7e, 0x18,
  0xd7, 0xf5, 0x0f, 0x86, 0x1f, 0x1a, 0xff, 0x00, 0xe0, 0xae, 0x7e, 0x3d,
  0xf8, 0x6f, 0xab, 0x6b, 0xbe, 0x10, 0xf1, 0x1d, 0x8e, 0x97, 0xe2, 0xdf,
  0x05, 0xeb, 0x7a, 0xbf, 0x85, 0x35, 0x1d, 0x4f, 0xc1, 0xbe, 0x34, 0xd1,
  0xbc, 0x3d, 0xe3, 0x4f, 0x0c, 0x5c, 0x69, 0x3e, 0x2d, 0xf0, 0xee, 0x85,
  0xad, 0x69, 0xff, 0x00, 0xa4, 0x9f, 0x03, 0x7e, 0x36, 0xe9, 0x9f, 0x1a,
  0xf4, 0xcf, 0x1a, 0xff, 0x00, 0xc5, 0x19, 0xe3, 0x8f, 0x86, 0x9e, 0x33,
  0xf8, 0x63, 0xe3, 0x86, 0xf8, 0x75, 0xf1, 0x47, 0xe1, 0x77, 0xc4, 0x41,
  0xe0, 0xf9, 0xbc, 0x5f, 0xf0, 0xf7, 0xc6, 0x73, 0x78, 0x3f, 0xc1, 0xff,
  0x00, 0x12, 0x34, 0x8d, 0x1f, 0x54, 0xd5, 0xbe, 0x1b, 0x78, 0xd3, 0xe2,
  0x37, 0xc3, 0x7d, 0x69, 0x35, 0xef, 0x86, 0x3f, 0x11, 0x3e, 0x1e, 0x7c,
  0x40, 0xd3, 0xaf, 0x3c, 0x0d, 0xf1, 0x03, 0xc5, 0xfa, 0x55, 0x9e, 0x93,
  0xe3, 0x4d, 0x3f, 0x43, 0xd6, 0x75, 0x0d, 0x23, 0xc6, 0xda, 0x3f, 0x8b,
  0x3c, 0x25, 0xe1, 0xb0, 0x0f, 0x1b, 0xf0, 0x18, 0x3f, 0xf0, 0xf1, 0xaf,
  0xda, 0xa8, 0xe3, 0x8f, 0xf8, 0x62, 0x8f, 0xd8, 0x09, 0x73, 0xdb, 0x70,
  0xf8, 0xe9, 0xff, 0x00, 0x05, 0x2a, 0x24, 0x67, 0xd4, 0x06, 0x52, 0x47,
  0x50, 0x19, 0x4f, 0x42, 0x2b, 0xed, 0x8a, 0xf8, 0x8f, 0xc0, 0x60, 0xff,
  0x00, 0xc3, 0xc6, 0x3f, 0x6a, 0x77, 0xda, 0xa4, 0xb7, 0xec, 0x55, 0xfb,
  0x02, 0x23, 0x64, 0xf3, 0x94, 0xf8, 0xe7, 0xff, 0x00, 0x05, 0x27, 0x3b,
  0x4b, 0x6c, 0x25, 0xd1, 0x09, 0x92, 0x48, 0xd8, 0xed, 0x7d, 0xee, 0xc1,
  0xbe, 0x56, 0x1e, 0x5f, 0xdb, 0x7c, 0xfa, 0x0f, 0xcc, 0xff, 0x00, 0x85,
  0x00, 0x2d, 0x7c, 0x4f, 0xfb, 0x2b, 0x02, 0x3e, 0x3a, 0xff, 0x00, 0xc1,
  0x4a, 0xf2, 0x31, 0x9f, 0xdb, 0x5f, 0xc0, 0x6c, 0x33, 0xdd, 0x7f, 0xe1,
  0xdc, 0xdf, 0xb0, 0x12, 0xe4, 0x7a, 0x8d, 0xca, 0xc3, 0x3d, 0x32, 0xa4,
  0x75, 0x06, 0xbe, 0xd6, 0x3b, 0xb0, 0x70, 0xaa, 0x4e, 0x0f, 0x05, 0x88,
  0x07, 0xd8, 0x9d, 0xa7, 0x00, 0xf7, 0xe0, 0xfd, 0x0d, 0x7c, 0x49, 0xfb,
  0x2b, 0xab, 0x7f, 0xc2, 0xf3, 0xff, 0x00, 0x82, 0x94, 0x15, 0x0b, 0xba,
  0x4f, 0xdb, 0x57, 0xc0, 0x92, 0x7d, 0xf2, 0x99, 0x03, 0xfe, 0x09, 0xd3,
  0xfb, 0x02, 0xa8, 0x77, 0x75, 0x8c, 0x93, 0x21, 0x50, 0x8a, 0x54, 0x2e,
  0xc0, 0x88, 0x80, 0x12, 0x54, 0xb3, 0x80, 0x7f, 0xff, 0xd9
};

// 32x32 jpg icon
unsigned char joyicon_jpeg[1070] = {
  0xff, 0xd8, 0xff, 0xe0, 0x00, 0x10, 0x4a, 0x46, 0x49, 0x46, 0x00, 0x01,
  0x01, 0x01, 0x00, 0x60, 0x00, 0x60, 0x00, 0x00, 0xff, 0xdb, 0x00, 0x43,
  0x00, 0x05, 0x03, 0x04, 0x04, 0x04, 0x03, 0x05, 0x04, 0x04, 0x04, 0x05,
  0x05, 0x05, 0x06, 0x07, 0x0c, 0x08, 0x07, 0x07, 0x07, 0x07, 0x0f, 0x0b,
  0x0b, 0x09, 0x0c, 0x11, 0x0f, 0x12, 0x12, 0x11, 0x0f, 0x11, 0x11, 0x13,
  0x16, 0x1c, 0x17, 0x13, 0x14, 0x1a, 0x15, 0x11, 0x11, 0x18, 0x21, 0x18,
  0x1a, 0x1d, 0x1d, 0x1f, 0x1f, 0x1f, 0x13, 0x17, 0x22, 0x24, 0x22, 0x1e,
  0x24, 0x1c, 0x1e, 0x1f, 0x1e, 0xff, 0xdb, 0x00, 0x43, 0x01, 0x05, 0x05,
  0x05, 0x07, 0x06, 0x07, 0x0e, 0x08, 0x08, 0x0e, 0x1e, 0x14, 0x11, 0x14,
  0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
  0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
  0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
  0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
  0x1e, 0x1e, 0xff, 0xc0, 0x00, 0x11, 0x08, 0x00, 0x20, 0x00, 0x20, 0x03,
  0x01, 0x22, 0x00, 0x02, 0x11, 0x01, 0x03, 0x11, 0x01, 0xff, 0xc4, 0x00,
  0x1f, 0x00, 0x00, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
  0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0xff, 0xc4, 0x00, 0xb5, 0x10, 0x00,
  0x02, 0x01, 0x03, 0x03, 0x02, 0x04, 0x03, 0x05, 0x05, 0x04, 0x04, 0x00,
  0x00, 0x01, 0x7d, 0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12, 0x21,
  0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07, 0x22, 0x71, 0x14, 0x32, 0x81,
  0x91, 0xa1, 0x08, 0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0, 0x24,
  0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x25,
  0x26, 0x27, 0x28, 0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a,
  0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x53, 0x54, 0x55, 0x56,
  0x57, 0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a,
  0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x83, 0x84, 0x85, 0x86,
  0x87, 0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99,
  0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3,
  0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6,
  0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9,
  0xda, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xf1,
  0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xff, 0xc4, 0x00,
  0x1f, 0x01, 0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
  0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0xff, 0xc4, 0x00, 0xb5, 0x11, 0x00,
  0x02, 0x01, 0x02, 0x04, 0x04, 0x03, 0x04, 0x07, 0x05, 0x04, 0x04, 0x00,
  0x01, 0x02, 0x77, 0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21, 0x31,
  0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71, 0x13, 0x22, 0x32, 0x81, 0x08,
  0x14, 0x42, 0x91, 0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0, 0x15,
  0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34, 0xe1, 0x25, 0xf1, 0x17, 0x18,
  0x19, 0x1a, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38, 0x39,
  0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x53, 0x54, 0x55,
  0x56, 0x57, 0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
  0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x82, 0x83, 0x84,
  0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
  0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa,
  0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4,
  0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
  0xd8, 0xd9, 0xda, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
  0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xff, 0xda, 0x00,
  0x0c, 0x03, 0x01, 0x00, 0x02, 0x11, 0x03, 0x11, 0x00, 0x3f, 0x00, 0xf9,
  0x67, 0xc1, 0x3e, 0x17, 0x7d, 0x6a, 0x43, 0x75, 0x74, 0x5a, 0x3b, 0x08,
  0xce, 0x09, 0x1d, 0x64, 0x3e, 0x83, 0xfa, 0x9a, 0xfa, 0xbb, 0xf6, 0x5f,
  0xf0, 0x27, 0x84, 0x75, 0x34, 0xd5, 0x45, 0xe6, 0x89, 0x6d, 0x30, 0xb5,
  0x11, 0x08, 0xb2, 0x0e, 0x46, 0xed, 0xd9, 0x24, 0x8e, 0x49, 0xf9, 0x47,
  0x5a, 0x7f, 0xc3, 0x5f, 0x80, 0xeb, 0x7d, 0xe0, 0x4d, 0x26, 0xe7, 0xfb,
  0x55, 0x6d, 0xbc, 0xdb, 0x70, 0xde, 0x58, 0x8f, 0x24, 0x1e, 0x72, 0x4f,
  0xb9, 0x3c, 0xfe, 0x35, 0xd1, 0xe9, 0x3a, 0x5d, 0xef, 0xc1, 0x1d, 0x4d,
  0xef, 0xee, 0xe5, 0xfe, 0xd2, 0xf0, 0xee, 0xa1, 0xb2, 0x2b, 0xa9, 0xa3,
  0x4c, 0x49, 0x6f, 0x20, 0xce, 0xd3, 0x8e, 0xe3, 0x93, 0xfe, 0x71, 0x90,
  0x0e, 0x53, 0xf6, 0xa5, 0xf0, 0x27, 0x84, 0x34, 0xb9, 0x34, 0x43, 0x65,
  0xa1, 0xda, 0xc1, 0xf6, 0xc5, 0x9c, 0x4d, 0xb4, 0x1c, 0xb6, 0xdf, 0x2f,
  0x69, 0xcf, 0x50, 0x7e, 0x63, 0xd3, 0xd6, 0xbe, 0x55, 0xf1, 0xaf, 0x86,
  0x1f, 0x45, 0x90, 0x5c, 0xdb, 0x16, 0x96, 0xc2, 0x43, 0x85, 0x63, 0xcb,
  0x21, 0xfe, 0xe9, 0xfe, 0x86, 0xbe, 0xd7, 0xd5, 0x74, 0x7b, 0xaf, 0x8d,
  0xb7, 0xa9, 0xab, 0x24, 0xc7, 0x4f, 0xd0, 0xac, 0x37, 0xc5, 0x64, 0xcc,
  0x99, 0x79, 0x98, 0x91, 0xbc, 0x91, 0xdb, 0xee, 0x8f, 0xcb, 0xeb, 0x8e,
  0x53, 0xe2, 0xc7, 0xc0, 0xc8, 0xb4, 0xaf, 0x87, 0x5a, 0xc5, 0xfa, 0xea,
  0xcb, 0x38, 0x82, 0x0d, 0xe6, 0x36, 0x4c, 0x67, 0x91, 0x8e, 0x7b, 0x10,
  0x70, 0x7f, 0x0a, 0x00, 0xb9, 0xf0, 0xcb, 0xe3, 0x94, 0x76, 0x7f, 0x0f,
  0xf4, 0x8b, 0x76, 0xd2, 0xd6, 0xe5, 0xa2, 0xb7, 0x0b, 0xe6, 0x2c, 0xbb,
  0x72, 0x79, 0xc8, 0x23, 0x1d, 0x41, 0xc8, 0xfc, 0x2b, 0xa5, 0xd0, 0xef,
  0x24, 0xf8, 0xd3, 0x79, 0x3c, 0x1a, 0x8a, 0x1b, 0x3d, 0x0b, 0x4e, 0xd8,
  0xd2, 0xdb, 0x23, 0x92, 0xd3, 0xc8, 0xc0, 0xed, 0xc9, 0xf4, 0xe0, 0xff,
  0x00, 0x93, 0x91, 0xf1, 0x2f, 0x81, 0xbc, 0x57, 0x26, 0x87, 0x21, 0xb4,
  0xba, 0x0d, 0x2d, 0x84, 0x87, 0x25, 0x47, 0x58, 0xcf, 0xf7, 0x87, 0xf5,
  0x15, 0xf5, 0x8f, 0xec, 0xbf, 0xe3, 0xaf, 0x08, 0xd8, 0x5b, 0xea, 0xe2,
  0xf3, 0x5c, 0xb4, 0x83, 0xed, 0x1e, 0x53, 0xc6, 0x5d, 0xb1, 0x9c, 0x6e,
  0xc8, 0x23, 0xa8, 0x23, 0x70, 0xe0, 0xd0, 0x06, 0xfe, 0xab, 0xa9, 0x5d,
  0xfc, 0x11, 0xd5, 0x63, 0xb0, 0xd3, 0xd4, 0x6a, 0x1a, 0x06, 0xa7, 0xbe,
  0x6b, 0x7b, 0x69, 0x9c, 0x87, 0xb7, 0x91, 0x76, 0xee, 0xc3, 0x7a, 0x1d,
  0xc3, 0xfc, 0x8c, 0x9e, 0x6b, 0xe2, 0xcf, 0xc6, 0xf3, 0xaa, 0xfc, 0x3b,
  0xd5, 0xec, 0x8e, 0x97, 0x15, 0xaa, 0xcf, 0x0e, 0xd2, 0xfe, 0x61, 0x63,
  0xd4, 0x60, 0x01, 0xea, 0x4e, 0x07, 0xe3, 0x51, 0xfe, 0xd4, 0x1e, 0x39,
  0xf0, 0x9e, 0xa5, 0x71, 0xa4, 0x35, 0xa6, 0xb7, 0x6b, 0x32, 0xda, 0xc5,
  0x29, 0x91, 0x91, 0xb3, 0xf7, 0x8a, 0xe0, 0x01, 0xd4, 0x9f, 0x94, 0xf4,
  0xaf, 0x95, 0xbc, 0x71, 0xe2, 0x99, 0x35, 0xc9, 0x45, 0xad, 0xb0, 0x68,
  0xec, 0x23, 0x39, 0x55, 0x3c, 0x34, 0x87, 0xfb, 0xc7, 0xfa, 0x0a, 0x00,
  0xff, 0xd9
};

unsigned char caution_jpg[] /* 64x46 */ = {
  0xff, 0xd8, 0xff, 0xe0, 0x00, 0x10, 0x4a, 0x46, 0x49, 0x46, 0x00, 0x01,
  0x01, 0x01, 0x00, 0x60, 0x00, 0x60, 0x00, 0x00, 0xff, 0xdb, 0x00, 0x43,
  0x00, 0x14, 0x0e, 0x0f, 0x12, 0x0f, 0x0d, 0x14, 0x12, 0x10, 0x12, 0x17,
  0x15, 0x14, 0x18, 0x1e, 0x32, 0x21, 0x1e, 0x1c, 0x1c, 0x1e, 0x3d, 0x2c,
  0x2e, 0x24, 0x32, 0x49, 0x40, 0x4c, 0x4b, 0x47, 0x40, 0x46, 0x45, 0x50,
  0x5a, 0x73, 0x62, 0x50, 0x55, 0x6d, 0x56, 0x45, 0x46, 0x64, 0x88, 0x65,
  0x6d, 0x77, 0x7b, 0x81, 0x82, 0x81, 0x4e, 0x60, 0x8d, 0x97, 0x8c, 0x7d,
  0x96, 0x73, 0x7e, 0x81, 0x7c, 0xff, 0xdb, 0x00, 0x43, 0x01, 0x15, 0x17,
  0x17, 0x1e, 0x1a, 0x1e, 0x3b, 0x21, 0x21, 0x3b, 0x7c, 0x53, 0x46, 0x53,
  0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c,
  0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c,
  0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c,
  0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c, 0x7c,
  0x7c, 0x7c, 0xff, 0xc0, 0x00, 0x11, 0x08, 0x00, 0x2e, 0x00, 0x40, 0x03,
  0x01, 0x22, 0x00, 0x02, 0x11, 0x01, 0x03, 0x11, 0x01, 0xff, 0xc4, 0x00,
  0x1f, 0x00, 0x00, 0x01, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
  0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0xff, 0xc4, 0x00, 0xb5, 0x10, 0x00,
  0x02, 0x01, 0x03, 0x03, 0x02, 0x04, 0x03, 0x05, 0x05, 0x04, 0x04, 0x00,
  0x00, 0x01, 0x7d, 0x01, 0x02, 0x03, 0x00, 0x04, 0x11, 0x05, 0x12, 0x21,
  0x31, 0x41, 0x06, 0x13, 0x51, 0x61, 0x07, 0x22, 0x71, 0x14, 0x32, 0x81,
  0x91, 0xa1, 0x08, 0x23, 0x42, 0xb1, 0xc1, 0x15, 0x52, 0xd1, 0xf0, 0x24,
  0x33, 0x62, 0x72, 0x82, 0x09, 0x0a, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x25,
  0x26, 0x27, 0x28, 0x29, 0x2a, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a,
  0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x53, 0x54, 0x55, 0x56,
  0x57, 0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a,
  0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x83, 0x84, 0x85, 0x86,
  0x87, 0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99,
  0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xb2, 0xb3,
  0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6,
  0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9,
  0xda, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xf1,
  0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xff, 0xc4, 0x00,
  0x1f, 0x01, 0x00, 0x03, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05,
  0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0xff, 0xc4, 0x00, 0xb5, 0x11, 0x00,
  0x02, 0x01, 0x02, 0x04, 0x04, 0x03, 0x04, 0x07, 0x05, 0x04, 0x04, 0x00,
  0x01, 0x02, 0x77, 0x00, 0x01, 0x02, 0x03, 0x11, 0x04, 0x05, 0x21, 0x31,
  0x06, 0x12, 0x41, 0x51, 0x07, 0x61, 0x71, 0x13, 0x22, 0x32, 0x81, 0x08,
  0x14, 0x42, 0x91, 0xa1, 0xb1, 0xc1, 0x09, 0x23, 0x33, 0x52, 0xf0, 0x15,
  0x62, 0x72, 0xd1, 0x0a, 0x16, 0x24, 0x34, 0xe1, 0x25, 0xf1, 0x17, 0x18,
  0x19, 0x1a, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x35, 0x36, 0x37, 0x38, 0x39,
  0x3a, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x53, 0x54, 0x55,
  0x56, 0x57, 0x58, 0x59, 0x5a, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69,
  0x6a, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x82, 0x83, 0x84,
  0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
  0x98, 0x99, 0x9a, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa,
  0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xc2, 0xc3, 0xc4,
  0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
  0xd8, 0xd9, 0xda, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea,
  0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xff, 0xda, 0x00,
  0x0c, 0x03, 0x01, 0x00, 0x02, 0x11, 0x03, 0x11, 0x00, 0x3f, 0x00, 0x6e,
  0xa1, 0xa8, 0xdd, 0x47, 0x7d, 0x14, 0x16, 0xf0, 0xc7, 0x34, 0x92, 0xc6,
  0x1c, 0x97, 0x5d, 0xc4, 0x93, 0x9f, 0xd2, 0xb5, 0x12, 0x19, 0x16, 0x10,
  0xd7, 0x0d, 0x02, 0xb0, 0x19, 0x6c, 0x47, 0xf2, 0x8f, 0xcc, 0xd2, 0x40,
  0xb1, 0x24, 0x8d, 0x3b, 0xed, 0x56, 0x58, 0x50, 0x17, 0x3d, 0x86, 0x09,
  0xae, 0x73, 0x5b, 0xd6, 0x9a, 0xf5, 0x8c, 0x10, 0x12, 0xb6, 0xe0, 0xf2,
  0x7b, 0xbf, 0xff, 0x00, 0x5a, 0xbc, 0x64, 0xa5, 0x5a, 0x5c, 0xb1, 0xd2,
  0xdb, 0xb3, 0x7d, 0x12, 0x25, 0xbb, 0xd7, 0xd9, 0x27, 0x65, 0xb6, 0x8e,
  0x07, 0x8c, 0x70, 0x19, 0xa3, 0xeb, 0xfa, 0xd6, 0xae, 0x99, 0xf6, 0xcb,
  0xb8, 0x3c, 0xeb, 0x98, 0xe0, 0x89, 0x5b, 0xee, 0x01, 0x17, 0x24, 0x7a,
  0xf5, 0xac, 0xfd, 0x0b, 0x44, 0x0d, 0xb6, 0xea, 0xf1, 0x78, 0xea, 0x91,
  0x9e, 0xfe, 0xe6, 0xae, 0x6b, 0x7a, 0xd2, 0xd9, 0xa9, 0x82, 0xd8, 0x83,
  0x39, 0x1c, 0x9e, 0xc9, 0xff, 0x00, 0xd7, 0xaa, 0xa9, 0x69, 0x4b, 0xd9,
  0x52, 0x5a, 0xf7, 0x05, 0xdd, 0x91, 0x6a, 0xfa, 0x9a, 0xe9, 0xec, 0x22,
  0x8b, 0xc9, 0x96, 0x6e, 0xe0, 0xc7, 0xc2, 0x8f, 0x7e, 0x6a, 0x2d, 0x2e,
  0xfe, 0xff, 0x00, 0x51, 0x9b, 0x6a, 0xc1, 0x6c, 0xb1, 0x2f, 0xdf, 0x7f,
  0x2f, 0xa7, 0xeb, 0xd6, 0xb2, 0xb4, 0xcd, 0x3a, 0x6d, 0x52, 0xe0, 0x92,
  0xc4, 0x46, 0x0e, 0x64, 0x90, 0xff, 0x00, 0x9e, 0x4d, 0x75, 0x53, 0x4f,
  0x69, 0xa3, 0x58, 0x80, 0x00, 0x54, 0x5e, 0x15, 0x07, 0x56, 0x34, 0xea,
  0x72, 0xd3, 0x4a, 0x9c, 0x75, 0x90, 0x96, 0xba, 0xf4, 0x1b, 0x7d, 0x2c,
  0x76, 0x16, 0xe6, 0x59, 0x9e, 0x3c, 0x7f, 0x0a, 0x88, 0x86, 0x58, 0xfa,
  0x0e, 0x6b, 0x33, 0x4b, 0xd6, 0x26, 0xbb, 0xb9, 0x91, 0x5a, 0x38, 0x93,
  0x64, 0x6d, 0x22, 0xb2, 0x2e, 0x08, 0x23, 0xa7, 0x35, 0x8f, 0x73, 0x71,
  0x73, 0xab, 0x5e, 0x8c, 0x82, 0xce, 0xc7, 0x08, 0x83, 0xa2, 0x8a, 0xe8,
  0x2d, 0x34, 0xb8, 0xf4, 0xe8, 0x09, 0x24, 0x3c, 0xef, 0x1b, 0xef, 0x6f,
  0x4e, 0x3a, 0x0a, 0x6e, 0x0a, 0x8c, 0x3d, 0xe7, 0xef, 0x30, 0xdd, 0xe8,
  0x53, 0xbf, 0xb4, 0x17, 0xda, 0xdd, 0xa4, 0x0c, 0xc5, 0x55, 0xa0, 0x5c,
  0x91, 0xd7, 0x03, 0x26, 0xa8, 0x5c, 0x43, 0x63, 0x71, 0x24, 0x51, 0xd8,
  0x09, 0x52, 0x56, 0x93, 0x61, 0x57, 0xe4, 0x11, 0xeb, 0x9a, 0xd4, 0xbd,
  0x82, 0xf7, 0xfb, 0x4e, 0xde, 0xe6, 0xca, 0x2f, 0x30, 0xc5, 0x0a, 0x67,
  0x91, 0x8e, 0xfc, 0x55, 0x39, 0xb5, 0x56, 0xb5, 0xba, 0x45, 0xfb, 0x0c,
  0x51, 0x79, 0x2e, 0x5c, 0xa0, 0x7c, 0xe5, 0x88, 0xc6, 0x73, 0xfd, 0x2b,
  0x48, 0x39, 0x3b, 0x72, 0xeb, 0xa7, 0x7f, 0xcf, 0xf0, 0x13, 0xf3, 0x27,
  0x93, 0x47, 0xb5, 0xfe, 0xd2, 0xb5, 0x8e, 0x22, 0xed, 0x6f, 0x2e, 0xf5,
  0x6f, 0x9b, 0x9d, 0xcb, 0x9c, 0xd5, 0x48, 0xad, 0x2d, 0x12, 0xc0, 0xdd,
  0x5c, 0x2c, 0x8c, 0x16, 0xe0, 0xc6, 0x42, 0x1e, 0x76, 0xe2, 0xad, 0x5a,
  0xdf, 0xea, 0x97, 0xb1, 0x23, 0xc7, 0x6c, 0x26, 0x68, 0xa5, 0xdc, 0x24,
  0xe1, 0x47, 0x4c, 0x11, 0x8e, 0xfd, 0x4d, 0x41, 0xac, 0x49, 0x72, 0xb6,
  0xc9, 0x0c, 0x96, 0x49, 0x69, 0x13, 0x39, 0x7c, 0x07, 0x04, 0xb3, 0x7a,
  0xd1, 0x1f, 0x69, 0xcc, 0xa1, 0x27, 0xf8, 0xfa, 0x86, 0x9b, 0x93, 0xcd,
  0x61, 0xa7, 0x2d, 0xed, 0xad, 0xac, 0x69, 0x30, 0x69, 0xb0, 0xe4, 0x96,
  0xe3, 0x69, 0x07, 0x8f, 0xaf, 0x15, 0x1a, 0x58, 0x58, 0xc1, 0x18, 0x92,
  0xec, 0x4a, 0xfe, 0x74, 0xed, 0x14, 0x61, 0x4f, 0xdd, 0x00, 0xe3, 0x26,
  0xa0, 0x8e, 0xfa, 0x7b, 0xbd, 0x4e, 0xd6, 0x58, 0x6d, 0xf7, 0xc9, 0x12,
  0x05, 0x08, 0x0f, 0x5c, 0x67, 0x9c, 0xf6, 0xeb, 0x57, 0x90, 0xdf, 0xdb,
  0xc4, 0xe6, 0xe7, 0x4e, 0x49, 0x23, 0x59, 0x0c, 0xca, 0x5d, 0xc0, 0xf2,
  0xc9, 0x39, 0xeb, 0x4a, 0x5c, 0xf1, 0xb2, 0x6f, 0xf1, 0xf5, 0x1e, 0x8c,
  0x67, 0xf6, 0x0a, 0x1b, 0x7b, 0xc5, 0x8d, 0x98, 0xcf, 0x14, 0x84, 0x47,
  0xcf, 0xde, 0x18, 0x07, 0x1f, 0x5c, 0x53, 0xa0, 0xb5, 0x8e, 0xcf, 0x5b,
  0xb8, 0x86, 0x1c, 0xec, 0x16, 0xcc, 0x79, 0x39, 0xea, 0x05, 0x67, 0xff,
  0x00, 0x6c, 0xcf, 0xb5, 0xbe, 0x51, 0xe6, 0x34, 0xe2, 0x6d, 0xe0, 0xf7,
  0xc6, 0x31, 0x8f, 0x4a, 0xd4, 0xb7, 0x5b, 0xa9, 0xb5, 0x19, 0x6f, 0x6e,
  0x2d, 0x8c, 0x2b, 0x25, 0xbb, 0x00, 0x33, 0x9e, 0xc2, 0x89, 0x2a, 0x91,
  0x4f, 0x9d, 0xe9, 0x6f, 0xf2, 0x0d, 0x3a, 0x06, 0xaf, 0xaa, 0x49, 0x64,
  0xa2, 0x08, 0x3e, 0x59, 0x24, 0x89, 0x0e, 0xff, 0x00, 0xee, 0x8c, 0x76,
  0xf7, 0xac, 0xdd, 0x23, 0x49, 0x93, 0x52, 0x97, 0x7b, 0xe5, 0x60, 0x53,
  0xf3, 0x37, 0x76, 0x3e, 0x82, 0xb5, 0x75, 0x6b, 0x2b, 0x59, 0x2e, 0xc2,
  0xdc, 0xbc, 0xc2, 0x48, 0x94, 0x21, 0xf2, 0xc0, 0xc1, 0x03, 0xeb, 0x56,
  0x62, 0xbf, 0x86, 0x18, 0xd6, 0x38, 0xb7, 0xaa, 0x28, 0xc0, 0x02, 0x31,
  0xc7, 0xeb, 0x50, 0xea, 0x7b, 0x38, 0x72, 0xc1, 0x7b, 0xdd, 0x42, 0xd7,
  0x7a, 0x93, 0xde, 0xde, 0x5b, 0x68, 0xf6, 0x6a, 0xa1, 0x40, 0xc0, 0xc4,
  0x71, 0xaf, 0x7f, 0xf3, 0xeb, 0x5c, 0x9b, 0x35, 0xd6, 0xaf, 0x7d, 0xde,
  0x49, 0x5f, 0xa0, 0xec, 0xa3, 0xfa, 0x0a, 0xd4, 0xba, 0xb6, 0xb4, 0xbc,
  0x9d, 0xa6, 0x9e, 0x7b, 0xb6, 0x73, 0xfe, 0xca, 0xe0, 0x0f, 0x41, 0x56,
  0x6c, 0x1e, 0xd3, 0x4f, 0x46, 0x58, 0x0c, 0xb9, 0x6e, 0xac, 0xc8, 0xa4,
  0x9f, 0xd6, 0xa6, 0x9c, 0xa1, 0x4a, 0x2d, 0xad, 0x64, 0xc6, 0xee, 0xdf,
  0x91, 0x7b, 0x4f, 0xb0, 0xb7, 0xd2, 0x2d, 0x59, 0x99, 0x86, 0xec, 0x66,
  0x49, 0x4f, 0xf9, 0xe9, 0x5c, 0xee, 0xb3, 0xac, 0x3e, 0xa0, 0xfe, 0x54,
  0x59, 0x5b, 0x75, 0x3c, 0x0e, 0xed, 0xee, 0x6b, 0x52, 0xfe, 0x48, 0x35,
  0x04, 0x54, 0x9a, 0x7b, 0x95, 0x41, 0xce, 0xd4, 0x55, 0x00, 0x9f, 0x7e,
  0x6a, 0xb5, 0xad, 0xa5, 0x85, 0xac, 0xeb, 0x2a, 0xb4, 0xee, 0xcb, 0xd0,
  0x3a, 0xa9, 0x00, 0xfa, 0xf5, 0xa5, 0x49, 0xc6, 0x2d, 0xd4, 0x9e, 0xb2,
  0x07, 0x7d, 0x91, 0x36, 0x85, 0xa1, 0xec, 0xdb, 0x75, 0x78, 0xbf, 0x37,
  0x54, 0x8c, 0xf6, 0xf7, 0x3e, 0xf5, 0x7e, 0xe6, 0xfa, 0x19, 0x6e, 0xde,
  0xd6, 0x33, 0xb9, 0xd2, 0x27, 0x66, 0x23, 0xa0, 0xe3, 0xa7, 0xd6, 0xa3,
  0x97, 0x51, 0x59, 0x23, 0x64, 0x12, 0xcc, 0x9b, 0x86, 0x37, 0x2a, 0x2e,
  0x47, 0xeb, 0x55, 0x74, 0xbb, 0x1b, 0x54, 0xbb, 0x22, 0x09, 0x27, 0x69,
  0x65, 0x52, 0x99, 0x90, 0x0c, 0x0c, 0xf5, 0x3c, 0x54, 0xab, 0xd5, 0x93,
  0x94, 0xde, 0xbd, 0x10, 0x6c, 0xb4, 0x3f, 0xff, 0xd9
};
unsigned int caution_jpg_len = 1557;
