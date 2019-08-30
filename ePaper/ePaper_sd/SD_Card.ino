#include <SPI.h>
#include <SD.h>
const int chipSelect = 5;
Sd2Card card;
SdVolume volume;
SdFile root;

void SD_setup() {
  //----------------------------------------------------------
  lg("\nInitializing SD card...");
  if (!card.init(SPI_HALF_SPEED, chipSelect)) {
    lgln("initialization failed. Things to check:");
    lgln("* is a card inserted?");
    lgln("* is your wiring correct?");
    lgln("* did you change the chipSelect pin to match your shield or module?");
    return;
  } else {
    lgln("Wiring is correct and a card is present.");
  }
  //----------------------------------------------------------
  lg("\nCard type: ");
  switch (card.type()) {
    case SD_CARD_TYPE_SD1: lgln("SD1"); break;
    case SD_CARD_TYPE_SD2: lgln("SD2"); break;
    case SD_CARD_TYPE_SDHC: lgln("SDHC"); break;
    default: lgln("Unknown");
  }
  //----------------------------------------------------------
  if (!volume.init(card)) {
    lgln("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
    return;
  }
  uint32_t volumesize;
  lg("\nVolume type is FAT"); lg(volume.fatType()); lg();
  //----------------------------------------------------------
  volumesize = volume.blocksPerCluster();
  volumesize *= volume.clusterCount();
  volumesize *= 512; volumesize /= 1048576;
  lg("Volume size (Mbytes): "); lg(volumesize); lg();
  //----------------------------------------------------------
  //lg("Volume size (bytes): "); lg(volumesize);lg();
  //lg("Volume size (Kbytes): "); volumesize /= 1024; lg(volumesize); lg();
  //lg("Volume size (Mbytes): "); volumesize /= 1024; lg(volumesize); lg();
  //----------------------------------------------------------
  lg("\nFiles found on the card (name, date and size in bytes): "); lg();
  root.openRoot(volume);
  root.ls(LS_R | LS_DATE | LS_SIZE);
  lg(); lg();
  //----------------------------------------------------------
}

