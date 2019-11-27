//** Created by Neal  Snooke on 24/10/2017.*/

#ifndef CODE_LOCATION_H
#define CODE_LOCATION_H

//#define DEBUG

/*
 * class to represent a location_
 */
class Location {

private:
    double lat_;
    double lng_;

public:
    static constexpr auto EARTH_RADIUS = 3440.07;
    static constexpr auto PI = 3.14159265358979323846;

    /**
     * @param lat
     * @param lng
     */
    Location(double lat, double lng);

    /**
     * initialise from file
     * @param file_in
     */
    Location(std::ifstream &file_in);

    /**
     * change the coordinates of this location
     * @param lat
     * @param lng
     */
    void setLocation(double lat, double lng);

    /**
     * @return latitude of this location
     */
    double getLatitude() const { return lat_; }

    /**
     * @return longitude of this location
     */
    double getLongitude() const { return lng_; }

    /**
     * calculate the great circle distance between this location and another
     * The code is based on the calculation as described on the web page
     * http://en.wikipedia.org/wiki/Great-circle_distance
     *
     * @return distance
     */
    double distance(const Location) const;

    /**
     * stream insertion operator overload to allow formatted stream output
     * @return the stream
     */
    friend std::basic_ostream<char>& operator<<(
            std::basic_ostream<char>&, const Location&);
};

#endif //CODE_LOCATION_H
