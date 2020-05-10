struct Word {
  uint8_t leds[8];
  uint8_t len;
};
const Word A = {{114},1};
const Word ITS = {{110,111,112}, 3};
const Word WAY = {{ 87, 86, 85}, 3};
const Word DAY = {{ 58, 57, 56}, 3};
const Word TWO = {{ 35, 34, 33}, 3};
const Word ONE = {{ 21, 20, 19}, 3};
const Word SIX = {{ 18, 17, 16}, 3};
const Word TIL = {{ 84, 83, 82}, 3};
const Word TEN_M = {{108,107,106}, 3};
const Word TEN_H = {{ 52, 53, 54}, 3};
const Word NINE = {{ 39, 38, 37, 36}, 4};
const Word HALF = {{116,117,118,119}, 4};
const Word FOUR = {{  0,  1,  2,  3}, 4};
const Word NOON = {{ 73, 74, 75, 76}, 4};
const Word PAST = {{ 81, 80, 79, 78}, 4};
const Word FIVE_M = {{ 95, 96, 97, 98}, 4};
const Word FIVE_H = {{ 43, 42, 41, 40}, 4};
const Word SEVEN = {{ 67, 68, 69, 70, 71}, 5};
const Word BIRTH = {{ 64, 63, 62, 61, 60}, 5};
const Word EIGHT = {{ 28, 29, 30, 31, 32}, 5};
const Word THREE = {{ 15, 14, 13, 12, 11}, 5};
const Word HAPPY = {{116,103, 94, 81, 72}, 5};
const Word TWENTY = {{ 88, 89, 90, 91, 92, 93}, 6};
const Word OCLOCK = {{  5,  6,  7,  8,  9, 10}, 6};
const Word ELEVEN = {{ 22, 23, 24, 25, 26, 27}, 6};
const Word QUARTER = {{105,104,103,102,101,100, 99},7};
const Word MIDNIGHT = {{ 44, 45, 46, 47, 48, 49, 50, 51} ,8};


uint8_t ledQue[121];
uint8_t ledQueLastIndex = 0;


void addWord(Word word){
  for(uint8_t i = 0; i<word.len; i++){
    ledQue[ledQueLastIndex] = word.leds[i];
    ledQueLastIndex++;
  }
}



void updateLedQue(){
  ledQueLastIndex = 0;
  
  DateTime time = rtc.now();
  uint8_t minutes = time.minute();
  uint8_t hours = time.hour();  
  
  addWord(ITS);

  boolean isA    = (minutes >= 13 && minutes <= 17) || (minutes >= 43 && minutes <= 47); // quarter
  boolean isPast = minutes >=  3 && minutes <= 32;
  boolean isTo = minutes >= 33 && minutes <= 57;

  if (isA) { addWord(A); }

  if      (minutes >= 58 || minutes <= 2)  {  addWord(OCLOCK); } //o'clock
  else if (minutes >= 3 && minutes <= 7)   {  addWord(FIVE_M); } //five past
  else if (minutes >= 8 && minutes <= 12)  {  addWord(TEN_M); } //ten past
  else if (minutes >= 13 && minutes <= 17) {  addWord(QUARTER); } //quarter past
  else if (minutes >= 18 && minutes <= 22) {  addWord(TWENTY); } //twenty past
  else if (minutes >= 23 && minutes <= 27) {  addWord(TWENTY); addWord(FIVE_M); } //twenty five past
  else if (minutes >= 28 && minutes <= 32) {  addWord(HALF); } //half past
  else if (minutes >= 33 && minutes <= 37) {  addWord(TWENTY); addWord(FIVE_M); } //twenty five to
  else if (minutes >= 38 && minutes <= 42) {  addWord(TWENTY); } //twenty to
  else if (minutes >= 43 && minutes <= 47) {  addWord(QUARTER); } //quarter to
  else if (minutes >= 48 && minutes <= 52) {  addWord(TEN_M); } //ten to
  else if (minutes >= 53 && minutes <= 57) {  addWord(FIVE_M); } //five to
   
  if(isPast) { addWord(PAST); }
  if(isTo) { addWord(TIL); hours = ((hours%12) + 1); }

  if     (hours == 0)      { addWord(MIDNIGHT); }
  else if (hours%12 == 1)  { addWord(ONE); }
  else if (hours%12 == 2)  { addWord(TWO); }
  else if (hours%12 == 3)  { addWord(THREE); }
  else if (hours%12 == 4)  { addWord(FOUR); }
  else if (hours%12 == 5)  { addWord(FIVE_H); }
  else if (hours%12 == 6)  { addWord(SIX); }
  else if (hours%12 == 7)  { addWord(SEVEN); }
  else if (hours%12 == 8)  { addWord(EIGHT); }
  else if (hours%12 == 9)  { addWord(NINE); }
  else if (hours%12 == 10) { addWord(TEN_H); }
  else if (hours%12 == 11) { addWord(ELEVEN); }
  else if (hours == 12)    { addWord(NOON); }

  if (minutes >= 58 || minutes <= 2) {  addWord(OCLOCK); } //o'clock *//* hours = ((hours%12) + 1); }
}
