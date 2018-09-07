// Frank Hulmes Project1A

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mp3Head.h"

#define BUFFERSIZE 64

// Global variables Head and Tail
mp3_t *head;
mp3_t *tail;



int main (int argc, char *argv[]){
  char buffer[BUFFERSIZE];
  int choice;
  int len;
  for(;;){
    printf("Enter the number of the operation to perform: \n");
    printf("1. Add a new mp3 \n");
    printf("2. Remove an artist \n");
    printf("3. Print forwards \n");
    printf("4. Print backwards \n");
    printf("5. Close the program \n");
    if (fgets(buffer, BUFFERSIZE , stdin) != NULL){
      len = (int) strlen(buffer);
      // Null terminate the input string
      buffer[len - 1] = '\0';
      // Convert the input to an int
      choice = atoi(buffer);
      if(choice == 1){
        // add an mp3
        appendMp3();

      }
      else if(choice == 2){
        // remove an artist
        removeMp3();
      }
      else if(choice == 3){
        // print forwards
        printForwards();
      }
      else if(choice == 4){
        // print backwards
        printBackwards();
      }
      else{
        free_list(head);
        break;
      }
    }
  }




}

int appendMp3(){
  // Creates a new mp3 node and appends it to the end of the list
  mp3_t *newMp3 = (mp3_t *)malloc(sizeof(mp3_t));
  char *artist = (char *) malloc(BUFFERSIZE * sizeof(char));
  char *title = (char *) malloc(BUFFERSIZE * sizeof(char));
  char *date = (char *) malloc(BUFFERSIZE * sizeof(char));
  char *runTimeIn = (char *) malloc(BUFFERSIZE * sizeof(char));
  // Get the title
  printf("Enter the song title: ");
  newMp3->title = dataInput(title);
  // newMp3->title = title;
  // Get the artists name
  printf("Enter the artist: ");
  newMp3->artist = dataInput(artist);
  // Get the release date
  printf("Enter the release date (MM/DD/YYYY): ");
  newMp3->date = dataInput(date);
  // Get the run time
  printf("Enter the length (in seconds): ");
  newMp3->runTime = atoi(dataInput(runTimeIn));

  // The added node is the last in the list
  newMp3->next = NULL;
  // Check if first mp3 added
  if(head == NULL){
    newMp3->prev = NULL;
    head = newMp3;
    tail = newMp3;
  }
  // Otherwise, add it onto the tail
  else{
    newMp3->prev = tail;
    tail->next = newMp3;
    tail = newMp3;
  }
  // Free the buffers
  free(artist);
  free(title);
  free(date);
  free(runTimeIn);
  free(newMp3);
  return 0;

}

int removeMp3(){
  // Removes all mp3 nodes with the specified artists' name
  char *name = (char *) malloc(BUFFERSIZE * sizeof(char));
  mp3_t **head_ref = &head;
  mp3_t **tail_ref = &tail;
  mp3_t *currentNode = head;
  printf("Enter the name of the artist to delete: \n");
  strcpy(name, dataInput(name));
  while(currentNode != NULL){
    if(strcmp(currentNode->artist, name) == 0){
      printf("DELETING ARTIST: %s \n", name);
      deleteMp3(head_ref, tail_ref, currentNode);
    }
    currentNode = currentNode->next;
  }
  free(name);
  return 0;
}

int deleteMp3(mp3_t **head_ref, mp3_t **tail_ref, mp3_t *del){
  /* base case */
  if(*head_ref == NULL || del == NULL){
    return 0;
  }

  /* If node to be deleted is head node */
  if(*head_ref == del){
    *head_ref = del->next;
  }
  if(del->next != NULL){
    del->next->prev = del->prev;
  }
  /* The node being deleted is the tail */
  else{
    *tail_ref = del->prev;
  }
  if(del->prev != NULL){
    del->prev->next = del->next;
  }
  free(del);
  return 0;
}

int printForwards(){
  // Prints the mp3 list starting from head -> tail
  mp3_t *currentNode = head;
  mp3Print(currentNode);
  while(currentNode->next != NULL){
    currentNode = currentNode->next;
    mp3Print(currentNode);
  }
  printf("\n");
  return 0;
}

int printBackwards(){
  // Prints the mp3 list from tail -> head
  mp3_t *currentNode = tail;
  mp3Print(currentNode);
  while(currentNode->prev != NULL){
    currentNode = currentNode->prev;
    mp3Print(currentNode);
  }
  printf("\n");
  return 0;
}

char *dataInput(char *field){
  // Takes in user input and stores into a string to return
  char buffer[BUFFERSIZE];
  int len;
  if (fgets(buffer, BUFFERSIZE , stdin) != NULL)
  {
    len = (int) strlen(buffer);
    buffer[len - 1] = '\0';
    field = (char *) malloc(len);
    strcpy(field, buffer);
  }
  printf("\n"); //Flush the buffer
  return field;
}

int mp3Print(mp3_t *input){
  // Prints out a given mp3
  printf("%s", input->title);
  printf(" by: %s", input->artist);
  printf("  [Released %s    Length: %d seconds]", input->date, input->runTime);
  printf("\n");
  return 0;
}

void free_list(mp3_t *head_ref){
  mp3_t *tmp;
  while(head_ref != NULL){
    tmp = head_ref;
    head_ref = head_ref->next;
    free(tmp->title);
    free(tmp->artist);
    free(tmp->date);
    free(tmp);
  }
}
