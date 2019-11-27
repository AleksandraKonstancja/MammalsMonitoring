/* Title: Cetacean mammals monitoring program - part 1
 * Author: alm82
 * Date: 06.12.2017
 *
 * Description:
 * This is a first of two programs analysing results of cetacean mammals observations performed in Cardigan Bay.
 * Program is responsible for calculating locations of Bottlenose Dolphins and Harbour Porpoise based on given
 * observers locations and sightings of mammals.
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <stdbool.h>

/* struct for calculated mammals locations */
struct results{
    double latitude;
    double longitude;
};

struct observerData{
    float latitude;
    float longitude;
    char id[5];
};

struct sightingData{
    char observerID[5];
    char mammalType;
    float bearing;
    float range;
};

/*
 * Parameters: olat - observer latitude, olong - observer longitude, bearing, range
 * Returns: res - struct with calculated results
 * This is a function responsible for calculating mammals locations  */
struct results Calculate(double olat, double olong, double bearing, double range){

    struct results res;
    double bgr = bearing * M_PI / 180.0;
    double olatr = olat * M_PI / 180.0;

    res.latitude = olat + (range *cos(bgr)) / 60.0;
    res.longitude = olong + (range * sin(bgr) / cos(olatr)) / 60;
    //  printf("Lat: %f Long: %f\n", res.latitude, res.longitude );
    return res;
}

/*
 * Parameters: *filename - name of the file to open, mode - ( for reading, writing or both )
 * Returns: filePointer - pointer to opened file
 * This function opens a specified file. If the file has been opened it returns a pointer to it,
 * if it has not - error message is printed and program ends.
 */
FILE *openFile(char *filename, char *mode){
    FILE *filePointer;
    filePointer = fopen(filename, mode);

    if( filePointer == NULL ){
        printf("Failed to open the file.\n");
        exit(EXIT_FAILURE);
    }
    return filePointer;
}

/*
 * Parameters: *filename - name of the file to read
 * Returns: lines - number of lines in the file
 * This function counts number of lines in a given file by reading each character and adding 1 to number of lines
 * whenever it finds a new line character.
 */
int getLinesNumber(char *filename){

    FILE *filePointer= openFile(filename, "r");
    int lines = 0;
    int character;

    do{
        character = fgetc(filePointer);
        if (character == '\n')
            lines++;
    }while(character != EOF);

    fclose(filePointer);

    return lines;

}

/*
 * Parameters: *Data - pointer to array of structs in which data will be saved, *filename - name of the file to read from,
 * lines - number of lines in that file
 * Returns: Data - array of structs filled with saved data
 * This function reads the observers data from specified file and saves it.
 */
struct observerData *readObserversData(struct observerData *Data, char *filename, int lines){

    int character;
    FILE *filePointer;

    printf("Reading from %s:\n", filename);

    filePointer = openFile(filename, "r");

    /* ignore the first line containing date and time */
    do{
        character = fgetc(filePointer);
    }while (character != '\n');

    for (int i = 0; i < lines; i++){
        fscanf(filePointer,"%s", Data[i].id);
        fscanf(filePointer, "%f", &Data[i].latitude);
        fscanf(filePointer, "%f", &Data[i].longitude);
        printf("ID: %s, Latitude: %f, Longitude: %f\n", Data[i].id, Data[i].latitude, Data[i].longitude);
    }

    fclose(filePointer);

    return Data;

}

/*
 * Parameters: *Data - pointer to array of structs in which data will be saved, *filename - name of the file to read from,
 * lines - number of lines in that file
 * Returns: Data - array of structs filled with saved data
 * This function reads the sightings data from a specified file and saves it.
 */
struct sightingData *readSightingsData(struct sightingData *Data, char *filename, int lines){

    FILE *filePointer;
    filePointer = openFile(filename, "r");

    printf("Reading from %s:\n", filename);

    for (int i = 0; i < lines; i++){
        fscanf(filePointer,"%s", Data[i].observerID);
        fscanf(filePointer, "%s", &Data[i].mammalType);
        fscanf(filePointer, "%f", &Data[i].bearing);
        fscanf(filePointer, "%f", &Data[i].range);
        printf("ID: %s, Mammal type: %s Bearing: %f, Range: %f\n",
               Data[i].observerID, &Data[i].mammalType, Data[i].bearing, Data[i].range);
    }

    fclose(filePointer);

    return Data;
}
/*
 * Parameters: latitude, longitude ( of a mammal )
 * Returns: true if mammal is in " our sea " and false otherwise
 */
bool inOurSea( double latitude, double longitude){

    /* set of " our sea " boundaries*/
    const double minLat = 52.0;
    const double maxLat = 52.833;
    const double maxLong = -4.0;
    const double minLong = -5.5;

    if (latitude > minLat && latitude < maxLat && longitude < maxLong && longitude > minLong)
        return true;
    else
        return false;
}
/*
 * Parameters: *filename - name of a file to write into, lineNum - size ( number of lines ) of an array with results,
 * *observersPtr - pointer to saved observers data, *sightingsPtr - pointer to saved sightings data
 * This function saves calculated mammals locations into a specified file.
 */
void writeData(char *filename, int lineNum, struct observerData *observersPtr, struct sightingData *sightingsPtr){
    FILE *filePointer = openFile(filename, "w");

    struct results results[lineNum];

    int j = 0;
    for (int i=0; i<lineNum; i++) {
        /* calculate mammals location for each of the sightings made by the same observer, then go to next observer */
        while (strcmp(observersPtr[i].id, sightingsPtr[j].observerID)== 0) {
            results[j] = Calculate(observersPtr[i].latitude, observersPtr[i].longitude, sightingsPtr[j].bearing,
                                   sightingsPtr[j].range);
            j++;
        }
    }

    printf("Calculated results:\n");

    for (int i=lineNum-1; i>=0; i--) {
        /* save results into file only if mammal is in " our sea " */
        if (inOurSea(results[i].latitude, results[i].longitude)) {
            printf("Mammal type: %s, Latitude: %f, Longitude: %f\n", &sightingsPtr[i].mammalType, results[i].latitude,
                   results[i].longitude);
            fprintf(filePointer, "%s",&sightingsPtr[i].mammalType);
            fprintf(filePointer, " %f ", results[i].latitude);
            fprintf(filePointer, "%f\n", results[i].longitude);
        }
    }
    fclose(filePointer);
}

/*
 * Main function responsible for interacting with user.
 */
int main() {

    char fullPath[60] = "../../";
    char filename[50];

    /* number of entries in observers and sightings files */
    int obSize, siSize;
    struct observerData *observersPtr;
    struct sightingData *sightingsPtr;

    printf("*** THIS IS THE CETACEAN MAMMAL MONITORING PROGRAM PART 1***\n"
                   "1.Please enter the name of file containing observers locations: ");
    scanf(" %s", filename);

    /* number of observers entries is equal to number of lines in the file - 1 as first line contains date and time */
    obSize = getLinesNumber(filename)-1;
    struct observerData observers[obSize];
    observersPtr = readObserversData(observers,filename, obSize);

    printf("2. Please enter the name of the file containing mammals sighting: ");
    scanf(" %s", filename);
    siSize = getLinesNumber(filename);
    struct sightingData sightings[siSize];
    sightingsPtr = readSightingsData(sightings, filename, siSize);

    printf("3. Please enter the target file name to save calculated locations:\n");
    scanf(" %s", filename);
    /* results will be saved outside the project folder, so that they are easy to reach for second program */
    strcat(fullPath, filename);

    /* used siSize here as number of calculated mammals locations should be equal to number of mammals sightings */
    writeData(fullPath,siSize,observersPtr,sightingsPtr);
    printf("\nAll done! Results have been saved to %s", fullPath);

    return (EXIT_SUCCESS);
}