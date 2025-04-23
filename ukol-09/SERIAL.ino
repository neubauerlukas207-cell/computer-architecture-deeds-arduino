const int MAX_SIZE = 10;
int matice[MAX_SIZE][MAX_SIZE];  // 10x10 pole
int rozmer = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Zadejte rozměr čtvercové matice (3–10):");
}

void loop() {
  if (Serial.available() > 0) {
    int vstup = Serial.parseInt();

    if (vstup >= 3 && vstup <= 10) {
      rozmer = vstup;
      naplnMatici();
      vypisMatici();

      // Zastav program (čekání navždy)
      while (true) {
        // Program skončí a nic dál se neděje
      }

    } else {
      Serial.println("Neplatný vstup. Zadejte číslo od 3 do 10:");
    }
  }
}

void naplnMatici() {
  int hodnota = 0;
  for (int i = 0; i < rozmer; i++) {
    for (int j = 0; j < rozmer; j++) {
      matice[i][j] = hodnota++;
    }
  }
}

void vypisMatici() {
  int min = matice[0][0];
  int max = matice[0][0];

  Serial.println("Vygenerovaná matice:");

  for (int i = 0; i < rozmer; i++) {
    for (int j = 0; j < rozmer; j++) {
      int cislo = matice[i][j];

      // Najdi min a max
      if (cislo < min) min = cislo;
      if (cislo > max) max = cislo;

      // Zarovnání podle velikosti čísla
      if (cislo < 10) Serial.print("  ");
      else if (cislo < 100) Serial.print(" ");
      Serial.print(cislo);
      Serial.print(" ");
    }
    Serial.println();
  }

  Serial.print("Nejmenší číslo: ");
  Serial.println(min);
  Serial.print("Největší číslo: ");
  Serial.println(max);
}
