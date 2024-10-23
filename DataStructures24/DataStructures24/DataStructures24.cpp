#include <iostream>    // Basic library for input and output
#include <algorithm>  // Library that contains many useful algorithms, such as sort
#include <vector>     // Library for creating dynamic arrays
#include <random>     // Library for generating random numbers
#include <string>     // Library for working with strings
#include <limits>     // Library that contains the maximum values of various data types
using namespace std; // Use the std namespace so that we don't need to write std::

///////////////////////////// DOUBLE LINKED LIST & ITS METHODS ///////////////////////////// 

template <class T>
class DoubleNode; // Forward declaration for DoubleNode

template <class T>
class Double {
private:
    DoubleNode<T>* LeftEnd, * RightEnd; // Pointers to the first and last nodes

public:
    Double() : LeftEnd(nullptr), RightEnd(nullptr) {} // Constructor for initializing pointers to nullptr
    ~Double(); // Destructor
    bool IsEmpty() const { return LeftEnd == nullptr; } // Function to check if the list is empty
    Double<T>& Insert(int k, const T& x); // Function to insert a node at a specific position
    Double<T>& Insert(const T& x); // Function to insert a node at the end
    void showData() const; // Function to display the data in the list
    void Delete(int k); // Function to delete a node at a specific position
    DoubleNode<T>* getNthNode(int n) const; // Function to get the nth node in the list
    int Size() const; // Function to get the size of the list
    void sortByAlphanumeric(string(T::* getFunc)() const); // Function to sort the list by alphanumeric order
    void sortByLikes(); // Function to sort the list by likes

    // Function to get a pointer to the LeftEnd node
    DoubleNode<T>* getFirstNode() const {
        return LeftEnd;
    }
};


template <class T>
class DoubleNode {
    friend class Double<T>;
private:
    T data;
    DoubleNode<T>* left, * right;
public:
    DoubleNode() : left(nullptr), right(nullptr) {} // Default constructor
    // Constructor to initialize data and links
    DoubleNode(const T& _data) : data(_data), left(nullptr), right(nullptr) {}
    T getData() const { return data; } // Getter function for data
    DoubleNode<T>* getLink() const { return right; } // Use right pointer to get the link
    DoubleNode<T>* getLeft() const { return left; } // Getter function for left pointer  
};


template <class T>
void Double<T>::sortByLikes() {
    // Check if there are one or fewer elements
    if (LeftEnd == nullptr || LeftEnd->right == nullptr)
        return;

    bool swapped;
    DoubleNode<T>* p;
    DoubleNode<T>* q = nullptr;

    // Bubble sort algorithm
    do {
        swapped = false;
        p = LeftEnd;

        // Traverse the list
        while (p->right != q) {
            // If current node has fewer likes than its next node, swap them
            if (p->data.getLikes() < p->right->data.getLikes()) {
                // Swap nodes
                DoubleNode<T>* temp = p->right;
                p->right = temp->right;
                if (temp->right)
                    temp->right->left = p; // Update the left link of the new right node
                temp->left = p->left;
                if (p->left)
                    p->left->right = temp; // Update the right link of the new left node
                temp->right = p;
                p->left = temp;

                // Update LeftEnd if necessary
                if (p == LeftEnd)
                    LeftEnd = temp;

                swapped = true;
            }
            else {
                p = p->right;
            }
        }
        q = p;
    } while (swapped);
}


template <class T>
void Double<T>::sortByAlphanumeric(string(T::* getFunc)() const) {
    // Check if there are one or fewer elements
    if (LeftEnd == nullptr || LeftEnd->right == nullptr)
        return;

    bool swapped;
    DoubleNode<T>* p;
    DoubleNode<T>* q = nullptr;

    // Bubble sort algorithm
    do {
        swapped = false;
        p = LeftEnd;

        // Traverse the list
        while (p->right != q) {
            // If current node's data retrieved by getFunc is greater than next node's data, swap them
            if ((p->data.*getFunc)() > (p->right->data.*getFunc)()) {
                // Swap nodes
                DoubleNode<T>* temp = p->right;
                p->right = temp->right;
                if (temp->right)
                    temp->right->left = p; // Update the left link of the new right node
                temp->left = p->left;
                if (p->left)
                    p->left->right = temp; // Update the right link of the new left node
                temp->right = p;
                p->left = temp;

                // Update LeftEnd if necessary
                if (p == LeftEnd)
                    LeftEnd = temp;

                swapped = true;
            }
            else {
                p = p->right;
            }
        }
        q = p;
    } while (swapped);
}


template <class T>
Double<T>::~Double() {
    // Start from LeftEnd and delete all nodes
    DoubleNode<T>* current = LeftEnd;
    while (current != nullptr) {
        DoubleNode<T>* next = current->right; // Traverse using the right pointer
        delete current;
        current = next;
    }
    LeftEnd = nullptr; // Set the LeftEnd pointer to nullptr after deleting all nodes
    RightEnd = nullptr; // Set the RightEnd pointer to nullptr after deleting all nodes
}


template <class T>
int Double<T>::Size() const {
    // Start from LeftEnd and count the number of nodes
    DoubleNode<T>* current = LeftEnd;
    int count = 0;
    while (current != nullptr) {
        count++;
        current = current->right; // Traverse using the right pointer
    }
    return count;
}


template <class T>
DoubleNode<T>* Double<T>::getNthNode(int n) const {
    // Start from LeftEnd and traverse to the nth node
    DoubleNode<T>* current = LeftEnd;
    int count = 0;
    while (current != nullptr && count < n) {
        current = current->right; // Traverse using the right pointer
        count++;
    }
    return current; // Return the nth node or nullptr if not found
}


template <class T>
void Double<T>::Delete(int k) {
    if (k < 0) {
        cout << "Invalid index!" << endl; // Print error message if index is negative
        return;
    }

    if (k == 0) {
        if (LeftEnd == nullptr) {
            cout << "List is empty!" << endl; // Print error message if list is empty
            return;
        }

        // Delete the first node
        DoubleNode<T>* temp = LeftEnd;
        LeftEnd = LeftEnd->right;
        if (LeftEnd)
            LeftEnd->left = nullptr; // Update the left pointer of the new first node
        delete temp;
        return;
    }

    // Traverse to the (k-1)th node
    DoubleNode<T>* p = LeftEnd;
    for (int index = 1; index < k && p->right != nullptr; index++)
        p = p->right;

    if (p->right == nullptr) {
        cout << "Invalid index!" << endl; // Print error message if index is out of bounds
        return;
    }

    // Delete the kth node
    DoubleNode<T>* temp = p->right;
    p->right = temp->right;
    if (temp->right)
        temp->right->left = p; // Update the left pointer of the next node
    delete temp;
}


// Inserts an element at a specific position in the list. If the user tries to insert at a position greater than the list size, it is appended at the end.
template <class T>
Double<T>& Double<T>::Insert(int k, const T& x) {
    if (k < 0) {
        cout << "Invalid index!" << endl; // Print error message if index is negative
        return *this;
    }

    DoubleNode<T>* y = new DoubleNode<T>(x); // Create a new node with the provided data

    if (k == 0 || IsEmpty()) { // Insert at the beginning if list is empty or k is 0
        y->right = LeftEnd;
        if (LeftEnd) {
            LeftEnd->left = y; // Update the left link of the old first node
        }
        LeftEnd = y;
        if (!RightEnd) { // If RightEnd is nullptr, then this is the first node in the list
            RightEnd = y;
        }
        return *this;
    }

    DoubleNode<T>* p = LeftEnd;
    int index = 1;
    while (index < k && p->right) {
        p = p->right;
        index++;
    }

    //If k is bigger than the index of the list it adds the element at the end of the list
    // Insert the new node between p and p->right
    y->left = p;
    y->right = p->right;
    if (p->right) {
        p->right->left = y; // Update the left link of the node after the new node
    }
    p->right = y;

    if (p == RightEnd) { // Update RightEnd if the new node is inserted at the end or if k is bigger than the index
        RightEnd = y;
    }

    return *this;
}


// Inserts an element at the end of the list
template <class T>
Double<T>& Double<T>::Insert(const T& x) {
    DoubleNode<T>* y = new DoubleNode<T>;
    y->data = x;
    y->left = nullptr;
    y->right = nullptr;

    if (LeftEnd == nullptr) { // If the list is empty
        LeftEnd = y;
    }
    else {
        DoubleNode<T>* p = LeftEnd;
        while (p->right != nullptr)
            p = p->right;

        p->right = y; // Insert new node at the end of the list
        y->left = p; // Update the left link of the new node
    }

    return *this;
}


template <class T>
void Double<T>::showData() const {
    // Traverse the list and print data of each node
    DoubleNode<T>* current = LeftEnd;
    while (current != nullptr) {
        cout << "Title: " << current->data.getTitle() << endl;
        cout << "Artist's Name: " << current->data.getArtistsName() << endl;
        cout << "Artist's Surname: " << current->data.getArtistsSurname() << endl;
        cout << "Album Title: " << current->data.getAlbumTitle() << endl;
        cout << "Likes: " << current->data.getLikes() << endl;
        cout << "-------------------------------" << endl;
        current = current->right; // Move to the next node using the right pointer
    }
    cout << endl;
}

///////////////////////////// SONG CLASS ///////////////////////////// 

class Song {
private:
    string title;
    string artists_name;
    string artists_surname;
    string album_title;
    int likes;

public:
    Song() : title(""), artists_name(""), artists_surname(""), album_title(""), likes(0) {} // Default constructor

    Song(const string& title, const string& artists_name, const string& artists_surname, const string& album_title, int likes)
        : title(title), artists_name(artists_name), artists_surname(artists_surname), album_title(album_title), likes(likes) {
    }

    string getTitle() const {
        return title;
    }

    string getArtistsName() const {
        return artists_name;
    }

    string getArtistsSurname() const {
        return artists_surname;
    }

    string getAlbumTitle() const {
        return album_title;
    }

    int getLikes() const {
        return likes;
    }
};

///////////////////////////// PLAYLIST CLASS ///////////////////////////// 

class Playlist {
private:
    string playlists_name;
    Double <Song> songs;
    DoubleNode<Song>* current_song; // Pointer to the currently playing song
    int current_song_index = 0; // Initialize current song index

public:

    // Constructor to initialize playlist name
    Playlist(const string& playlists_name) : playlists_name(playlists_name) {};

    // Add a song to the playlist at a specific position
    void addSongToPlaylist(int position, const Song& newSong) {
        songs.Insert(position, newSong);
    }

    // Add a song to the end of the playlist
    void addSongToPlaylist(const Song& newSong) {
        songs.Insert(newSong);
    }

    // Display playlist data, including its name and all songs
    void showPlaylistData() const {
        cout << "Playlist: " << playlists_name << endl;
        cout << "Songs:" << endl;
        songs.showData();
    }

    // Sort the playlist by alphanumeric order based on a member function of Song
    template <class T>
    void SortByAlphanumeric(string(T::* getFunc)() const) {
        songs.sortByAlphanumeric(getFunc);
    }

    // Sort the playlist by number of likes
    void SortByLikes() {
        songs.sortByLikes();
    }

    // Play the next song in the playlist
    void playNextSong() {
        if (songs.IsEmpty()) {
            cout << "No songs in the playlist!" << endl;
            return;
        }

        if (current_song == nullptr || current_song->getLink() == nullptr) {
            // If there's no current song playing or if the current song is the last one,
            // reset current_song to the first song
            current_song = songs.getFirstNode();
            current_song_index = 0; // Reset current song index
        }
        else {
            // Move to the next song
            current_song = current_song->getLink();
            current_song_index++; // Increment current song index
        }

        // Display information about the currently playing song
        cout << "Playing song \"" << current_song->getData().getTitle() << "\" from the album \""
            << current_song->getData().getAlbumTitle() << "\" with singer \""
            << current_song->getData().getArtistsName() << " "
            << current_song->getData().getArtistsSurname() << "\" ("
            << current_song->getData().getLikes() << " users like this song)" << endl;
    }

    // Play the previous song in the playlist
    void playPreviousSong() {
        if (songs.IsEmpty()) {
            cout << "No songs in the playlist!" << endl;
            return;
        }

        // If there's no current song playing, set current_song to the first song
        if (current_song == nullptr) {
            cout << "No song is currently playing." << endl;
            return;
        }

        // Get the previous song
        DoubleNode<Song>* prev_song = current_song->getLeft();

        // If there is no previous song, i.e., current song is the first song in the playlist
        if (prev_song == nullptr) {
            cout << "No previous song. You are already at the beginning of the playlist playing the 1st song." << endl;
            return;
        }

        // Set current song to the previous song
        current_song = prev_song;

        // Decrement current song index
        current_song_index--;

        // Display information about the currently playing song
        cout << "Playing song \"" << current_song->getData().getTitle() << "\" from the album \""
            << current_song->getData().getAlbumTitle() << "\" with singer \""
            << current_song->getData().getArtistsName() << " "
            << current_song->getData().getArtistsSurname() << "\" ("
            << current_song->getData().getLikes() << " users like this song)" << endl;
    }


    // Display all songs in the playlist in random order
    void showAllSongsRandomly() {
        if (songs.IsEmpty()) {
            cout << "No songs in the playlist!" << endl;
            return;
        }

        // Create a vector of song pointers
        vector<DoubleNode<Song>*> songPointers;
        DoubleNode<Song>* current = songs.getFirstNode();
        while (current != nullptr) {
            songPointers.push_back(current);
            current = current->getLink();
        }

        // Shuffle the vector
        random_device rd;
        mt19937 rng(rd());
        shuffle(songPointers.begin(), songPointers.end(), rng);

        // Display the songs in random order
        for (DoubleNode<Song>* songNode : songPointers) {
            cout << "Playing song \"" << songNode->getData().getTitle() << "\" from the album \""
                << songNode->getData().getAlbumTitle() << "\" with singer \""
                << songNode->getData().getArtistsName() << " "
                << songNode->getData().getArtistsSurname() << "\" ("
                << songNode->getData().getLikes() << " users like this song)" << endl;
        }
    }

    void transferSong(int fromPosition, int toPosition) {
        // Check if fromPosition and toPosition are valid
        if (fromPosition < 0 || fromPosition > songs.Size() || toPosition < 0 || toPosition > songs.Size()) {
            cout << "Invalid positions! Positions should be between 1 and " << songs.Size() << endl;
            return;
        }

        // Get the node at the fromPosition
        DoubleNode<Song>* fromNode = songs.getNthNode(fromPosition);
        if (!fromNode) {
            cout << "Invalid from position!" << endl;
            return;
        }

        // Get the node at the toPosition
        DoubleNode<Song>* toNode = songs.getNthNode(toPosition);
        if (!toNode) {
            cout << "Invalid to position!" << endl;
            return;
        }

        // Remove the song from the fromPosition
        Song songToTransfer = fromNode->getData();
        songs.Delete(fromPosition);

        // Insert the song at the toPosition
        songs.Insert(toPosition, songToTransfer);

        // Inform the user about the transfer
        cout << "Song '" << songToTransfer.getTitle() << "' transferred to position " << toPosition + 1 << endl;
    }

};

///////////////////////////// INSERTING SONGS TO THE LIST ///////////////////////////// 

void static InitializePlaylist(Playlist& playlist)
{
    Song song1("Bohemian Rhapsody", "Freddie", "Mercury", "A Night at the Opera", 6842);
    Song song2("Social Cues", "Cage the", "Elephant", "Social Cues", 5109);
    Song song3("ZARI", "Marina", "Satti", "ZARI", 3138);
    Song song4("Adiakopa", "Foivos", "Delivorias", "Exo", 2953);
    Song song5("Oloi Xoreuoun Me Thn K.", "Yorgos", "Rous", "Rous", 1234);
    Song song6("The Yawning Grave", "Lord", "Huron", "Strange Trails", 3478);
    Song song7("Riptide", "Vance", "Joy", "Dream Your Life Away", 1042);
    Song song8("Girl, You'll Be a Woman Soon", "Urge", "Overkill", "Stull - EP", 5527);
    Song song9("The Code", "Nemo", "Melter", "The Code", 8042);

    playlist.addSongToPlaylist(song1);
    playlist.addSongToPlaylist(song2);
    playlist.addSongToPlaylist(song3);
    playlist.addSongToPlaylist(song4);
    playlist.addSongToPlaylist(song5);
    playlist.addSongToPlaylist(song6);
    playlist.addSongToPlaylist(song7);
    playlist.addSongToPlaylist(song8);
    playlist.addSongToPlaylist(song9);
}

///////////////////////////// MAIN FUNCTION ///////////////////////////// 

int main()
{
    int answer;
    Playlist playlist1("Favourites");
    InitializePlaylist(playlist1);

    // Main menu loop
    do {
        cout << "1. Insert new song into playlist \n"
            << "2. Play next song in playlist \n"
            << "3. Play previous song in playlist \n"
            << "4. Play all songs in playlist in random order \n"
            << "5. Move song to another position in playlist \n"
            << "6. Sort playlist \n"
            << "7. Print playlist to screen \n"
            << "8. Exit \n"
            << "Choose a number: ";

        // Input validation loop
        do {
            if (!(cin >> answer) || answer < 1 || answer > 8) {
                cout << "Please choose a number between 1 and 8: ";
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
        } while (answer < 1 || answer > 8);

        switch (answer) {
        case 1: {
            // Insert new song into playlist
            string title, singersName, singersSurname, titleOfAlbum;
            int likes, position;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl << "Enter title of song : ";
            getline(cin, title);

            cout << "Enter name of singer : ";
            getline(cin, singersName);

            cout << "Enter surname of singer : ";
            getline(cin, singersSurname);

            cout << "Enter title of album : ";
            getline(cin, titleOfAlbum);

            cout << "Enter number of likes : ";
            do {
                if (!(cin >> likes) || likes < 0) {
                    cout << "Please enter a non-negative integer: ";
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                }
            } while (likes < 0);

            cout << "Enter position in playlist : ";
            do {
                if (!(cin >> position) || position < 1) {
                    cout << "Please enter a positive integer: ";
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                }
            } while (position < 1);
            cout << endl;

            Song new_song(title, singersName, singersSurname, titleOfAlbum, likes);
            playlist1.addSongToPlaylist(position - 1, new_song);

            break;
        }
        case 2:
            cout << endl;
            // Play next song in playlist
            playlist1.playNextSong();
            cout << endl;
            break;
        case 3:
            cout << endl;
            // Play previous song in playlist
            playlist1.playPreviousSong();
            cout << endl;
            break;
        case 4:
            // Play all songs in playlist in random order
            cout << endl;
            playlist1.showAllSongsRandomly();
            cout << endl;
            break;
        case 5: {
            // Move song to another position in playlist
            int pos1, pos2;
            cout << endl;
            cout << "Enter position of song in playlist to move: ";
            cin >> pos1;
            cout << "Enter new position of song in playlist :";
            cin >> pos2;
            playlist1.transferSong(pos1 - 1, pos2 - 1);
            cout << endl;
            break;
        }
        case 6:
            // Sort playlist
            int ans;
            cout << endl;
            cout << "What type of sorting do you want to do? \n"
                << "1. Sort playlist by song title \n"
                << "2. Sort playlist by singer's first name \n"
                << "3. Sort playlist by singer's last name \n"
                << "4. Sort playlist by number of likes (decreasing) \n"
                << "5. Cancel \n"
                << "Choose an option between 1-5: ";
            do {
                if (!(cin >> ans) || ans < 1 || ans > 5) {
                    cout << "Please choose a number between 1 and 5: ";
                    cin.clear(); // Clear the error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                }
            } while (ans < 1 || ans > 5);
            switch (ans) {
            case 1:
                playlist1.SortByAlphanumeric(&Song::getTitle);
                cout << "The list has been sorted by title, press 7 to view the new list. \n" << endl;
                break;
            case 2:
                playlist1.SortByAlphanumeric(&Song::getArtistsName);
                cout << "The list has been sorted by the singer's first name, press 7 to view the new list. \n" << endl;
                break;
            case 3:
                playlist1.SortByAlphanumeric(&Song::getArtistsSurname);
                cout << "The list has been sorted by the singer's last name, press 7 to view the new list. \n" << endl;
                break;
            case 4:
                playlist1.SortByLikes();
                cout << "The list has been sorted by how many people liked the video, press 7 to view the new list. \n" << endl;
                break;
            case 5:
                break;
            }
            cout << endl;
            break;
        case 7:
            // Print playlist to screen
            cout << endl;
            playlist1.showPlaylistData();
            break;
        case 8:
            cout << "Shut Down of the Program";
            break;
        }
    } while (answer != 8);
    return 0;
}