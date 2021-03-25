// MISO - pin 12
// MOSI - pin 11
// SCK - pin 13
// CS - pin 4

String sdFileName;
bool sdInited = false;
int sdRowNumber = 0;
unsigned long sdTime = 0;

void sdSetup() {
  sdRowNumber = 0;
  // контакт, подключенный к CS-линии SD-карты
  sdInited = SD.begin(4);
  if (sdInited) {
    Serial.println("SD card initialized.");
    sdFileName = sdNextFileName("ut", ".csv");

    String dataString = "i\tV\tA\tW\tmWh\tmAh\tRl\tTime";
    File dataFile = SD.open(sdFileName, FILE_WRITE);
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      Serial.println(dataString);
    } else {
      Serial.print("error opening ");
      Serial.println(sdFileName);
    }
  } else {
    Serial.println("SD card failed, or not present");
  }
}

String sdNextFileName(String fName, String ext) {
  String r;
  if (!sdInited) {
    return r;
  }
  for (int i = 1; i < 512; i++) {
    r = "" + fName + i + ext;
    // Check to see if the file exists:
    if (SD.exists(r)) {
      Serial.print("SD file: ");
      Serial.print(r);
      Serial.println(" exists.");
    } else {
      Serial.print("SD file: ");
      Serial.print(r);
      Serial.println(" doesn't exist.");
      break;
    }
  }
  return r;
}

void sdLoop() {
  sdTime++;
  if (!sdInited) {
    return;
  }
  if (_adcA <= configMinA) {
    return;
  }
  sdRowNumber++;
  if (sdRowNumber > 32000) {
    sdFileName = sdNextFileName("ut", ".csv");
    sdRowNumber = 0;
  }

  float v = adcV();
  float a = adcA();
  unsigned long c = adcC();
  float rl = adcRl();
  unsigned int t = adcTime();
  unsigned long mWh = adcMWh();

  String dataString = "" + String(sdTime) + "\t" + String(v) + "\t" + String(a) + "\t" + String(v * a) + "\t" + String(mWh) + "\t" + String(c) + "\t" + String(rl) + "\t" + String(t);
  File dataFile = SD.open(sdFileName, FILE_WRITE);
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    Serial.println(dataString);
  } else {
    Serial.print("error opening ");
    Serial.println(sdFileName);
  }
}

bool sdIsInited() {
  return sdInited;
}

String sdGetFileName() {
  return sdFileName;
}
