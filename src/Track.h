// Music In-Memory Storage and Lookup System
// Specification file for the Track class

#ifndef TRACK_H
#define TRACK_H

#include <iostream>
using std::string;

class Track
{
private:
    string id;
    string name;
    string artist;
    string album;
    int length;
    int plays;

public:
    Track() { id = ""; name = ""; artist = ""; album = ""; length = 0; plays = 0; }  // Constructor
    Track(string i, string n, string ar, string al, int l, int p) { id = i; name = n; artist = ar; album = al; length = l; plays = p; }  // Overloaded Constructor

    // Setters and getters
    void setId(string i) { id = i; }
    void setName(string n) { name = n; }
    void setArtist(string ar) { artist = ar; }
    void setAlbum(string al) { album = al; }
    void setLength(int l) { length = l; }
    void setPlays(int p) { plays = p; }
    string getId() const { return id; }
    string getName() const { return name; }
    string getArtist() const { return artist; }
    string getAlbum() const { return album; }
    int getLength() const { return length; }
    int getPlays() const { return plays; }

    // overloaded operators
    bool operator==(const Track& track)
    {
        return (name == track.name);
    }
    bool operator<(const Track& track)
    {
        return (name < track.name);
    }
    bool operator>(const Track& track)
    {
        return (name > track.name);
    }
    friend std::ostream& operator << (std::ostream& output, const Track& track)
    {
        output << track.getName();
        return output;
    }

};

class TrackHash : public Track 
{
public:
    TrackHash() { setId(""); setName(""); setArtist(""); setAlbum(""); setLength(0); setPlays(0); }  // Constructor
    TrackHash(string i, string n, string ar, string al, int l, int p)
    {setId(i); setName(n); setArtist(ar); setAlbum(al); setLength(l); setPlays(p); }  // Overloaded Constructor
    // overloaded operators
    bool operator==(const TrackHash& track)
    {
        return (getId() == track.getId());
    }
    bool operator<(const TrackHash& track)
    {
        return (getId() < track.getId());
    }
    bool operator>(const TrackHash& track)
    {
        return (getId() > track.getId());
    }
    friend std::ostream& operator << (std::ostream& output, const TrackHash& track)
    {
        output << track.getName();
        return output;
    }
};
#endif
