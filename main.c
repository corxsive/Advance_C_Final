#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

int PRICE_LENGTH = 17161; //csv.length - header
int STRING_MAX_SIZE = 1024;

void readPriceCsv(char from[PRICE_LENGTH][50], char to[PRICE_LENGTH][50], int* adult, int* elder, int* child) {
    FILE* price = fopen("price.csv", "r");

    char useless[5][STRING_MAX_SIZE]; // For Header

    // handle FileNotFoundException
    if(!price){fprintf(stderr, "file to open csv file"); return 1;}

    fseek(price, 0, SEEK_SET);

    char line[STRING_MAX_SIZE]; // for storage csv.eachLine
    char* result = NULL; // for storage csv.eachLine.split(',')
    int count = 0; // while loop indicator
    while(fgets(line, STRING_MAX_SIZE, price) != NULL){
        result = strtok(line, ","); 
        for(int i=0; i<5; i++){
            // printf("%d - %d: %s\n", count, i, result); // *Debug Only
            if(count == 0){
                strncpy(useless[i], result, strlen(result) + 1); // Header
            } else {
                switch(i) {
                    case 0: // From
                        strcpy(from[count-1], result);
                        break;
                    case 1: // To
                        strcpy(to[count-1], result);
                        break;
                    case 2: // Price of Adult
                        adult[count-1] = atoi(result);
                        break;
                    case 3: // Price of Elder
                        elder[count-1] = atoi(result);
                        break;
                    case 4: // Price of Children
                        child[count-1] = atoi(result);
                        break;
                }
            }
            result = strtok(NULL, ",");
        }
        count++; // Indicator++ : prevent infinity loop
    }

    fclose(price);
}

int main() {
    setlocale(LC_ALL, "UTF-8"); // set for chinese character ! useless?

    #pragma region hardCode

    char alias[135][100] = {
        // BR - 文湖線
        "BR01","BR02","BR03","BR04","BR05","BR06","BR07","BR08","BR09","BR10",
        "BR11","BR12","BR13","BR14","BR15","BR16","BR17","BR18","BR19","BR20",
        "BR21","BR22","BR23","BR24",
        // R - 淡水信義線
        "R02","R03","R04","R05","R06","R07","R08","R09","R10","R11",
        "R12","R13","R14","R15","R16","R17","R18","R19","R20","R21",
        "R22","R22A","R23","R24","R25","R26","R27","R28",
        // G - 松山新店線
        "G01","G02","G03","G03A","G04","G05","G06","G07","G08","G09",
        "G10","G11","G12","G13","G14","G15","G16","G17","G18","G19",
        // O - 中和新蘆線
        "O01","O02","O03","O04","O05","O06","O07","O08","O09","O10",
        "O11","O12","O13","O14","O15","O16","O17","O18","O19","O20",
        "O21","O50","O51","O52","O53","O54",
        // BL - 板南線
        "BL01","BL02","BL03","BL04","BL05","BL06","BL07","BL08","BL09","BL10",
        "BL11","BL12","BL13","BL14","BL15","BL16","BL17","BL18","BL19","BL20",
        "BL21","BL22","BL23",
        // Y - 環狀線
        "Y07","Y08","Y09","Y10","Y11","Y12","Y13","Y14","Y15","Y16",
        "Y17","Y18","Y19","Y20"
    };
    char alias_CHI[135][100] = {
        // BR - 文湖線
        "動物園","木柵","萬芳社區","萬芳醫院","辛亥","麟光","六張犁","科技大樓","大安","忠孝復興",
        "南京復興","中山國中","松山機場","大直","劍南路","西湖","港墘","文德","內湖","大湖公園",
        "葫洲","東湖","南港軟體園區","南港展覽館",
        // R - 淡水信義線
        "象山","台北101/世貿","信義安和","大安","大安森林公園","東門","中正紀念堂","台大醫院","台北車站","中山",
        "雙連","民權西路","圓山","劍潭","士林","芝山","明德","石牌","唭哩岸","奇岩",
        "北投","新北投","復興崗","忠義","關渡","竹圍","紅樹林","淡水",
        // G - 松山新店線
        "新店","新店區公所","七張","小碧潭","大坪林","景美","萬隆","公館","台電大樓","古亭",
        "中正紀念堂","小南門","西門","北門","中山","松江南京","南京復興","台北小巨蛋","南京三民","松山",
        // O - 中和新蘆線
        "南勢角","景安","永安市場","頂溪","古亭","東門","忠孝新生","松江南京","行天宮","中山國小",
        "民權西路","大橋頭","台北橋","菜寮","三重","先嗇宮","頭前庄","新莊","輔大","丹鳳",
        "迴龍","三重國小","三和國中","徐匯中學","三民高中","蘆洲",
        // BL - 板南線
        "頂埔","永寧","土城","海山","亞東醫院","府中","板橋","新埔","江子翠","龍山寺",
        "西門","台北車站","善導寺","忠孝新生","忠孝復興","忠孝敦化","國父紀念館","市政府","永春","後山埤",
        "昆陽","南港","南港展覽館",
        // Y - 環狀線
        "大坪林","十四張","秀朗橋","景平","景安","中和","橋和","中原","板新","板橋",
        "新埔民生","頭前庄","幸福","新北產業園區"
    };

    // Print Alias code to screen
    for(int i=0; i<135; i++){
        printf("%s - %s    ", alias[i],alias_CHI[i]);
        if(i == 23 || i == 51 || i == 71 || i == 97 || i == 120 || i == 134){
            printf("\n");
        } else {
            printf("   \t");
        }
    }

    //parameters
    char input[100];
    int index_start = -1, index_end = -1;
    printf("Enter the code of your **Starting Point**:\n");
    while(index_start < 0){ // set index when found string
        scanf("%s", &input);
        for(int i=0; i<135; i++){
            if(strcmp(alias[i], input) == 0){ // ! Code Only
                index_start = i;
            }
        }
    }

    printf("Enter the code of your **Destination**:\n");
    while(index_end < 0 || index_end == index_start){
        scanf("%s", &input);
        for(int i=0; i<135; i++){
            if(strcmp(alias[i], input) == 0){ // ! Code Only
                index_end = i;
            }
        }
    }

    #pragma endregion hardCode

    #pragma region readPrice

    char from[PRICE_LENGTH][50], to[PRICE_LENGTH][50];
    int adult[PRICE_LENGTH], elder[PRICE_LENGTH], child[PRICE_LENGTH];
    readPriceCsv(from, to, adult, elder, child);

    #pragma endregion readPrice
    
    #pragma region printPrice
    
    for(int i=0; i<PRICE_LENGTH; i++){
        if(strcmp(alias_CHI[index_start], from[i]) == 0 && strcmp(alias_CHI[index_end], to[i]) == 0){
            printf("Location: %s -> %s\n\nPrice:\nAdult - %d\tElder - %d\tChild - %d\n",
            from[i], to[i], adult[i], elder[i], child[i]);
        }
    }

    #pragma endregion printPrice
}