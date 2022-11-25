#include "project.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


struct Driver{   //  Käytetty struct ja sen sisältämät ominaisuudet.
	char* lastName;
    char* teamName;
    int hours;
    int minutes;
    int seconds;
};


void memory_release(struct Driver *drivers, int size){ //Nollataan struct Drivers *driversin elementeille varatut muistit.
    for (int i = 0; i < size; i++) { 
        free(drivers[i].lastName);
        free(drivers[i].teamName);
    }
    free(drivers);
}

struct Driver *add_driver(struct Driver *drivers, char* name, char* team, int i){

    drivers = realloc(drivers, sizeof(struct Driver)*(i+1));   // Varataan muistia uuden driverin lisäämistä varten.
    if (drivers == NULL)  {         // Tarkastetaan, onnistuiko muistinvaraus.
        printf("Couldn't add the driver.\n");
        return NULL;
    }

    drivers[i].lastName = malloc(strlen(name)+1);    // Varataan muistia nimelle ja kopiopidaan parametri uuden Driverin lastName muuttujaan.
    strcpy(drivers[i].lastName, name);

    drivers[i].teamName = malloc(strlen(team)+1);    // Varataan muistia joukkueelle ja kopiopidaan parametri uuden Driverin teamName muuttujaan.
    strcpy(drivers[i].teamName,team);

    drivers[i].hours = 0;               // Alustetaan int muuttujat nollaan.
    drivers[i].minutes = 0;
    drivers[i].seconds = 0;

    printf("SUCCESS\n");
    return drivers;     // Palautetaan uusi struct Driver *drivers, johon on lisätty uusi kuljettaja.
}

void time_update(struct Driver *drivers, int i, int hours, int minutes, int seconds){
   
   int minutesSum = drivers[i].minutes + minutes;     // Tallennetaan int muuttujaan lisäyksen johdosta muodostuneet kokonaisminuutit.
   int secondsSum = drivers[i].seconds + seconds;     // Tallennetaan int muuttujaan lisäyksen johdosta muodostuneet kokonaissekunnit.   
	
    drivers[i].hours += hours;    
	
    if(minutesSum > 59){     // Tarkastetaan, ylittävätkö kokonaisminuutit 59 minuutin eli tunnin rajan.
	     drivers[i].minutes = minutesSum-60;
         drivers[i].hours += 1;
	    }
	    else{
	     drivers[i].minutes = minutesSum;  
	    }
	
	    if(secondsSum > 59){       // Tarkastetaan, ylittävätkö kokonaissekunnit 59 sekunnin eli minuutin rajan.
	     drivers[i].seconds = secondsSum-60;
	     drivers[i].minutes += 1;
	    }
	    else{
	     drivers[i].seconds = secondsSum;  
	    }
	    printf("SUCCESS\n"); 
}



void ordering(struct Driver *sortedDrivers, int i){

    struct Driver temporary;            // Käytetään Driver rakennetta, johon tallennetaan väliaikaisesti Driver-elementtejä, jotta niiden paikkoja voidaan alkuperäisessä struct Driver *driversissä muuttaa.
    
    for(int k=0; k<i; k++){           // Käydään läpi lista useaan kertaan, koska tällöin kaikki on lopulta järjestelty.
        for(int j=0; j<(i-1); j++) {
            if(sortedDrivers[j].hours > sortedDrivers[j+1].hours){   // Jos jälkimmäisen tunnit on pienempiä vaihdetaan peräkkäisten elementtien paikkaa.
               temporary = sortedDrivers[j];
               sortedDrivers[j] = sortedDrivers[j+1];
               sortedDrivers[j+1] = temporary;
            }
            else if(sortedDrivers[j].hours == sortedDrivers[j+1].hours){    // Jos tunnit ovat yhtäsuuret, käytetään toista ehtoa.
                 if(sortedDrivers[j].minutes > sortedDrivers[j+1].minutes){    // Jos jälkimmäisen minuutit on pienempiä vaihdetaan peräkkäisten elementtien paikkaa.
                    temporary = sortedDrivers[j];
                    sortedDrivers[j] = sortedDrivers[j+1];
                    sortedDrivers[j+1] = temporary;
                 }
                 else if(sortedDrivers[j].minutes == sortedDrivers[j+1].minutes){   // Jos minuutit ovat yhtäsuuret, käytetään toista ehtoa.
                    if(sortedDrivers[j].seconds > sortedDrivers[j+1].seconds){     // Jos jälkimmäisen sekunnit on pienempiä vaihdetaan peräkkäisten elementtien paikkaa.
                       temporary = sortedDrivers[j];
                       sortedDrivers[j] = sortedDrivers[j+1];
                       sortedDrivers[j+1] = temporary;
                 }
                }
            }
        }
    }
}

void print_race(struct Driver *drivers, int i){
    ordering(drivers,i); //Järjestään struct Driver *drivers ajoajan mukaan.

    if(i == 0){     // Tarkastetaan, onko kisassa ajajia.
        printf("Race has no drivers\n");
    }
    
    for(int j=0; j<i; j++){
        if(drivers[j].lastName == NULL) continue;     // Jos Driverin nimi on NULL, ohitetaan tämä.
        printf("%s %s %d %d %d\n", drivers[j].lastName, drivers[j].teamName, drivers[j].hours, drivers[j].minutes, drivers[j].seconds);  // Printataan Kuljettajat
    }

    if(i != 0){  // Jos kuljettajia on, tulostetaan onnistumisviesti.
       printf("SUCCESS\n"); 
    }
}


void saveToFile(char *filename, struct Driver *drivers, int i) {   // Funktio tallentaa kuljettajien tiedot tekstitiedostoon.
    FILE *f = fopen(filename,"w");   // Avataan tiedosto kirjoittamista varten.
    
    if(!f)  {    // Tarkistetaan, voidaanko tiedosto avata.
        printf("Couldn't open the file.\n");
    }

    else{
       for(int j = 0; j < i; j++){
        fprintf(f,"%s %s %d %d %d \n", drivers[j].lastName, drivers[j].teamName, drivers[j].hours, drivers[j].minutes, drivers[j].seconds); //Tulostetaan kaikki Driverin taulukon muuttujat tiedostoon *filename
       }
       printf("SUCCESS\n");
    }
    fclose(f);
}

int count_rows(FILE *f){  // Funktio, joka laskee tiedoston rivien määrän, jota käytetään download_info funktiossa.
    char cHar;
    int row = 0;

    while ((cHar = fgetc(f)) != EOF)    {
        if (cHar == '\n') //Kun cHar on rivinvaihtomerkki, lisätään rivien määrää.
            row++;
    }
    return row;    // Palauta rivien määrä.
}

struct Driver  *download_info(char *filename, struct Driver *drivers, int i){   // Funktio, joka lataa tiedostosta kuljettajien nimet ja sijoittaa ne Driver taulukkoon. 
   
    FILE *f = fopen(filename, "r");
    if(!f)  {    // Tarkistetaan, voidaanko tiedosto avata.
         printf("Couldn't open the file.\n");
         return drivers;
    }

    else{
    memory_release(drivers,i); // Tyhjennetään vanhan Driver taulukon muisti.

    int rows = count_rows(f);  // Lasketaan arrayn elementtien määrä.
    rewind(f);    // Palataan tiedoston alkuun.

    struct Driver *newDrivers = malloc((rows + 1) * sizeof(struct Driver)); // Varataan muistia Driver taulukolle.

    char lastName[1000];    // Driverin muuttujat
    char teamName[1000];
    int hours;
    int minutes;
    int seconds;
    
    for (int i=0; i<rows; i++){
        fscanf(f, "%s %s %d %d %d",  lastName, teamName, &hours, &minutes, &seconds); // Tallennetaan tiedot tiedostosta omiin muuttujiinsa
        
        newDrivers[i].lastName = malloc(strlen(lastName)+1);       // Varataan muistia nimelle ja kopiopidaan tiedostosta ladattu tieto parametri uuden Driverin lastName muuttujaan.
        strcpy(newDrivers[i].lastName, lastName);

        newDrivers[i].teamName = malloc(strlen(teamName)+1);       // Varataan muistia joukkueelle ja kopiopidaan tiedostosta ladattu tieto uuden Driverin lastName muuttujaan.
        strcpy(newDrivers[i].teamName,teamName);

        
        newDrivers[i].hours = hours;             // Kopioidaan tiedostosta int muuttujien tiedot.
        newDrivers[i].minutes = minutes;
        newDrivers[i].seconds = seconds;
    }

    fclose(f);
    printf("SUCCESS\n");
    return newDrivers; //Palautetaan uudet kuljettajat.
    }
}




int main(void){

    struct Driver *drivers = malloc(sizeof(struct Driver));     // Varataan muistia ja alustetaan Driver taulukko.

    char command[1000];           // Kaikki main funktion tarvitsemat char ja int muuttujat.
    char secondInput[1000];
    char thirdInput[1000];
    char input[1000];
    int size = 0;
    int index = 0;
    int runCondition = 0;
    int hoursInput = 0;
    int minutesInput = 0;
    int secondsInput = 0;
   
    
    while(runCondition == 0) {
        fgets(input, 1000, stdin); // Pyytää syötettä käyttäjältä.
        sscanf(input,"%s", command); // Katsotaan käyttäjän antama komento.
        
        switch(command[0]){ // Katsotaan mikä toimenpide vastaa kyseista komentoa.
            case 'A':
                if(sscanf(input,"%s %s %s", command, secondInput, thirdInput) == 3){   // Jokaisen komennon alla on ensimmäisena sscanf, joka tarkistaa syötteen oikeellisuuden.
                    int j = 0;
                    while(j<size && drivers != NULL){     // Tarkistetaan, onko saman niminen kuljettaja jo tietokannassa. Ehtona on sama nimi, mutta ei samaa joukkuetta/tallia.
                      if(drivers[j].lastName != NULL){
                        if(strcmp(secondInput, drivers[j].lastName) == 0){
                          printf("Driver \"%s\" already exists in the database.\n", secondInput);
                          break;
                        }
                      }
                      j++;
                    }
                    if(j==size || drivers == NULL){     // Jos j on sama kuin size, kuljettajaa tietyllä nimellä ei ole vielä tietokannassa.
                      drivers = add_driver(drivers, secondInput, thirdInput, size);   // Lisätään kuljettaja.
                      if(drivers == NULL){   // Jos drivers on NULL, myös kuljettajien määrä on nolla.
                        size = 0;
                      }  
                      size++;     // Lisää kuljettajien määrää.
                    }
                }
                else{
                    printf("A should be followed by exactly 2 arguments.\n");
                }
                break;
            case 'U':
                if(sscanf(input,"%s %s %d %d %d", command, secondInput, &hoursInput, &minutesInput, &secondsInput) == 5){
                    if(size == 0){     // Tarkistetaan erilaisia ehtoja liittien kuljettajan ajan päivittämiseen.
                      printf("Race has no drivers.\n");
                      break;
                    }   
                    if(drivers == NULL){
                      printf("Race has no drivers.\n");
                      break;
                    }  
                    if(hoursInput < 0){
                        printf("Hours cannot be negative.\n");
                        break;
                    }
                    if(minutesInput < 0 || minutesInput > 59){
                        printf("Minutes cannot be negative or greater than 59.\n");
                        break;
                    }
                    if(secondsInput < 0 || secondsInput > 59){
                        printf("Seconds cannot be negative or greater than 59.\n");
                        break;
                    }
                    index = 0;
                        while(index<size && drivers != NULL){
	                        if(drivers[index].lastName != NULL){
	                           if(strcmp(secondInput, drivers[index].lastName) == 0){  // Päivitetään kuljettajan aika, jos kuljettaja on tietokannassa. 
	                            time_update(drivers, index, hoursInput, minutesInput, secondsInput);  // Päivitetään kuljettajan aika.
	                            break;        
	                           }
	                        }
	                        index++;
	                    }
                    if(index == size) printf("Driver \"%s\" doesn't exist in the database.\n", secondInput);          // Tulostetaan viesti, jos kuljettajaa ei ole tietokannassa.
                }
                else{
                    printf("U should be followed by exactly 4 arguments.\n");
                }
                break;
            case 'L':
                if(sscanf(input,"%s", command) == 1){
                    if(drivers == NULL){      // Tarkastetaan, onko tietokanta tyhjä.
                      printf("Race has no drivers.\n");
                      break;
                    }
                    if(size == 0){
                      printf("Race has no drivers.\n");
                      break;
                    }
                    print_race(drivers, size);  // Tulostetaan tietokannan tiedot.
            
                }
                else{
                    printf("Invalid input.\n");
                }
                break;
            case 'W':
                if(sscanf(input,"%s %s",command, secondInput)==2){
                    if(drivers == NULL){     // Tarkastetaan, onko tietokanta tyhjä.
                      printf("Race has no drivers. Can't save anything to a textfile.\n");
                      break;
                    }
                    saveToFile(secondInput,drivers,size);   // Kirjoitetaan tekstitiedostoon tietokannan tiedot.
                }
                else  {
                    printf("Invalid input.\n");
                }
                break;
            case 'O':
                if(sscanf(input,"%s %s",command, secondInput) == 2 && drivers != NULL){ // Tarkistetaan syötteen oikeellisuus, ja että tietokanta ei ole tyhjä.
                    drivers = download_info(secondInput,drivers, size);   // Kirjoitetaan tiedoston tiedot tietokantaan.
                }
                else  {
                    printf("Invalid input or unable to download from file.\n");
                }
                break;
            case 'Q':
                if(sscanf(input,"%s",command) == 1)    {
                    if(drivers != NULL){  // Tarkastetaan, että tietokanta ei ole tyhjä.
                    memory_release(drivers, size); //Tyhjennetään tietokannassa varattu muisti.
                    }
                    printf("SUCCESS\n"); 
                    runCondition=1;
                }
                else  {
                    printf("Invalid input.\n");
                }
                break;
            default:
                printf("Invalid command %s\n" , command);  // Perus virheilmoitus, jos käyttäjä kirjoittaa komennon väärin.
        }
    }
    return 0;
}

