// Header file for all functions used in mp3

/* ===================================================================
      struct mp3 - node in a doubly linked list simulating an mp3 file
      fields:
        char *title = title of the mp3
        char *artist = artist of the song
        char *date = date song was released (MM/DD/YYYY)
        int runTime = length of song in seconds
        mp3 *next = next node in the list
        mp3 *prev = previous node in the list
  ====================================================================*/
typedef struct mp3 {
    char *title;
    char *artist;
    char *date;
    int runTime;
    struct mp3 *next;
    struct mp3 *prev;
}mp3_t;
/* ===================================================================
      append() - creates a new mp3 using user input and adds it to the end of
      the list
      returns 0
  ====================================================================*/

  int appendMp3();

/* ===================================================================
        removemp3() - prompts the user for the name of the artist and uses
        deleteMp3 to remove it from the list
        returns 0
  ====================================================================*/

  int removeMp3();
/* ===================================================================
        deleteMp3() - removes a given node from the free_list
        parameters: head_ref - pointer to the head node of the list
                    del - node to be deleted
        returns 0
  ====================================================================*/

  int deleteMp3(mp3_t **head_ref, mp3_t **tail_ref, mp3_t *del);

/* ===================================================================
        printForwards() - prints the linked list from head->tail
        returns 0
  ====================================================================*/

  int printForwards();
/* ===================================================================
        printBackwards() - prints the linked list from tail->head
        returns 0
  ====================================================================*/

  int printBackwards();
/* ===================================================================
        dataInput() - takes in user input and returns it as a null-terminated
        string
        parameters: field - string buffer
        returns: field - user input placed inside the buffer
  ====================================================================*/

  char *dataInput(char *field);
/* ===================================================================
        mp3Print() - takes in an mp3 node and prints it out
        parameters: input - the mp3 node to be printed
        returns 0
  ====================================================================*/

  int mp3Print(mp3_t *input);

/* ===================================================================
        free_list() - frees the memory of each node in the list
        parameters: head_ref- the pointer to the head node
  ====================================================================*/

  void free_list(mp3_t *head_ref);
