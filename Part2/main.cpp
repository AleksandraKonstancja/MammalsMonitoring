/*
 * Title: Cetacean mammals monitoring program - part 2
 * Author: alm82
 * Date: 12.12.2017
 *
 * Description:
 * This is a second of two programs analysing results of cetacean mammals observations performed in Cardigan Bay.
 * Program is responsible for finding entries that refer to the same mammal and replacing them with corrected
 * location of this mammal. It also identifies pods that mammals are swimming in.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include "MammalData.h"

/*
 * Parameters: mammalsList - list of mammals
 * Returns - mamalList - updated
 * This function checks if there are entries referring to the same mammal and if there are, it replaces them
 * with one entry with corrected location.
 */
std::vector<MammalData> findRepeatingMammals(std::vector<MammalData> mammalsList){

    /* compare each mammal from the list with every mammal that is in the list after it */
    for (int i = 0; i< mammalsList.size(); i++ ){
        for (int j = i+1; j< mammalsList.size(); j++){

            if (mammalsList[i].getMammalType() == mammalsList[j].getMammalType() &&
                (mammalsList[i].getLocation().distance(mammalsList[j].getLocation()) < 0.02)) {

                /* calculate real location - average of two entries locations */
                Location realLocation = Location(
                        (mammalsList[i].getLocation().getLatitude() + mammalsList[j].getLocation().getLatitude()) / 2,
                        (mammalsList[i].getLocation().getLongitude() + mammalsList[j].getLocation().getLongitude()) / 2
                );

                MammalData realMammal =MammalData(realLocation,mammalsList[i].getMammalType());
                /* delete entries that refer to the same mammal */
                mammalsList.pop_back();
                mammalsList.pop_back();
                /* add corrected entry */
                mammalsList.push_back(realMammal);

            }
        }
    }
    return mammalsList;
}

/*
 * Parameters: &filename - name of a file to read from
 * Returns: mammalList - final version
 * This function reads the calculated mammal data from a specified file and saves it. After saving each entry
 * the function looks for entries referring to the same mammal.
 * */
std::vector<MammalData> readMammalData(std::string &filename){

    std::ifstream file;
    char mammalType;
    /* list to save entries into */
    std::vector<MammalData> mammalsList;
    /* number of entries saved */
    int entriesSaved = 0;

    file.open(filename);

    if (file.is_open()) {

        while (file.good()) {
            file >> mammalType;
            Location loc = Location(file);
            MammalData mammal = MammalData(loc, mammalType);
            mammalsList.push_back(mammal);
            entriesSaved++;
            /* when there are at least two entries saved, search for repeating mammals starts */
            if (entriesSaved>0)
                mammalsList = findRepeatingMammals(mammalsList);
        }

       std::cout << "\nThe true locations of mammals:\n" <<
                  "There have been " << mammalsList.size() << " mammals observed in total.\n";
        for(int i=0; i<mammalsList.size(); i++){
            std::cout << i+1 << ". " << mammalsList[i].getMammalType() << ' ' << mammalsList[i].getLocation() << '\n';
        }
    }
    else{
        std::cout << "Failed to open the file";
    }
    file.close();

    return mammalsList;
}

/*
 * Parameters: mammal, pod
 * Returns: true - if mammal is iin a given pod, false - otherwise
 */
bool isInPod (MammalData mammal,std::vector<MammalData> pod) {
    for (int i=0; i<pod.size(); i++){
        if (pod[i].getLocation().distance(mammal.getLocation()) == 0)
        return true;
    }
    return false;
}

/*
 * Parameters: mammalsList - list of the mammals, startpos - position in the list at which it starts looking for
 * mammals in pod
 * Returns: endpos - position in the list where a pod finishes
 */
int findPod(std::vector<MammalData> mammalsList, int startpos, int podNumber) {

    std::vector<MammalData> pod;
    int endpos = 0;

    for (int i = startpos; i < mammalsList.size(); i++) {
        for (int j = i + 1; j < mammalsList.size(); j++) {

            double distance = mammalsList[i].getLocation().distance(mammalsList[j].getLocation());

            /* if there are no mammals in a pod yet and a pair of mammals with distance smaller than 0.1 is found
             * - both of them are added to the pod*/
            if (pod.empty() && mammalsList[i].getMammalType() == mammalsList[j].getMammalType() && distance < 0.1) {
                pod.push_back(mammalsList[i]);
                pod.push_back(mammalsList[j]);
                endpos = j;
            }
                /* if pod is not empty and distance between current mammal and any mammal that already is in the pod
                 * is smaller than 0.1, current mammal is added to the pod */
            else if (mammalsList[i].getMammalType() == mammalsList[j].getMammalType() &&
                     distance < 0.1 && isInPod(mammalsList[i], pod) && !isInPod(mammalsList[j], pod)) {
                pod.push_back(mammalsList[j]);
                /* end position is updated every time a mammal is added to the pod so that at the end it is position
                 * of last mammal in current pod*/
                endpos = j;
            }

        }
    }

    /* If pod is not empty size of pod and its contents ( mammals and their locations ) are printed */
    if (!pod.empty()) {
        std::cout << podNumber + 1 << ". " << "Consists of " << pod.size() << " mammals:\n";

        for (int i = 0; i < pod.size(); i++) {
            std::cout << pod[i].getMammalType() << ' ' << pod[i].getLocation() << ", ";
        }
        std::cout << '\n';
        return endpos;
    } else{
        return -1;
    }
}

/*
 * Parameters: mammalsList - list of mammals
 * This function is responsible for finding all pods in the mammals list. It starts looking for pods at first position
 * in the list and keeps looking for them until last pod is found.
 */
void findAllPods(std::vector<MammalData> &mammalsList){

    int startPosition = 0;
    int podsNumber = 0;

    std::cout<< "\nMammals are swimming in following pods:"  <<'\n';

    /* when position returned by findPod equal to -1 it means that pod was empty - there are no more pods in the list */
    do {
        startPosition = findPod(mammalsList, startPosition, podsNumber);
        podsNumber++;
    }while (startPosition != -1 );

    /* last pod is always an empty one so it is ignored */
    std::cout<< "In total " << podsNumber-1 << " pods have been observed.";

}

/* Main function responsible for interacting with user. */
int main() {

    std::string fullPath = "../../";
    std::string filename;

    std::vector<MammalData> mammalsList;

    std::cout << "*** THIS IS THE CETACEAN MAMMAL MONITORING PROGRAM PART 2 ***\n"
            << "1.Please enter the name of file containing calculated mammals locations:  ";
    std::cin >> filename;

    /* file needs to be in the folder that first program saves to - outside both projects */
    fullPath = fullPath + filename;

    mammalsList = readMammalData(fullPath);

    findAllPods(mammalsList);

    return 0;
}