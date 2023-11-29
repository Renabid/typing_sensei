#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define max_sentence_length 500
#define max_filename_length 100

//to select difficulty level
void generatesentence(char sentence[max_sentence_length], int difficulty);

//to save result in a file
void saveresult(char sentence[max_sentence_length], float typingspeed, float accuracy);

int main() {
    srand(time(NULL));

    int difficulty;
    printf("Select your difficulty level:\n1.Easy\n2.Medium\n3.Hard\n");
    scanf("%d", &difficulty);

    char sentence[max_sentence_length];
    generatesentence(sentence, difficulty);
   
    printf("Type the following sentence:\n%s\n", sentence);

    //start time
    time_t starttime = time(NULL);

    char userinput[max_sentence_length];
    getchar(); //to consume newline character
    fgets(userinput, max_sentence_length, stdin);

    //end time
    time_t endtime = time(NULL);

    //typing speed and accuracy
    int elapsedsecond = (int)difftime(endtime, starttime);
    int typedcharacters = strlen(userinput) - 1; //-1 to exclude newline
    int correctcharacters = 0;

    for (int i = 0; i < typedcharacters; ++i) {
        if (userinput[i] == sentence[i]) {
            correctcharacters++;
        }
    }

    float typingspeed = (float)typedcharacters / elapsedsecond;
    float accuracy = (float)correctcharacters / typedcharacters * 100;

    printf("\nTyping speed: %.2f characters per second\n", typingspeed);
    printf("Typing accuracy: %.2f%%\n", accuracy);

    //savedfile
    saveresult(sentence, typingspeed, accuracy);

    return 0;
}

void generatesentence(char sentence[max_sentence_length], int difficulty) {
    const char *easysentence[] = {
        "Join us in programming world.",
        "C is case-sensitive language.",
        "This is our first project"
    };

    const char *mediumsentence[] = {
        "Programming is a valuable skill in this modern world.",
        "The quick brown fox jumps over the lazy dog.",
        "Efficient time management is essential for productivity in both professional and personal endeavors"
    };

    const char *hardsentence[] = {
        "Amidst the cacophony of honking horns, blaring sirens, and bustling city life, the intrepid detective meticulously examined the crime scene, searching for elusive clues to solve the perplexing mystery that had left the entire community in suspense.",
        "As the sun dipped below the horizon, casting a warm, golden glow across the tranquil ocean, a solitary figure, shrouded in a flowing cloak, stood pensively on the weathered cliff's edge, contemplating the vastness of the universe and the intricacies of human existence.",
        "As the tempest raged with furious winds, torrential rain, and blinding flashes of lightning, the seasoned mariner, undeterred by the relentless forces of nature, skillfully navigated the treacherous waters in a valiant attempt to reach the safety of the distant harbor."
    };

    const char **sentences;
    int numsentences;

    switch (difficulty) {
    case 1:
        sentences = easysentence;
        numsentences = sizeof(easysentence) / sizeof(easysentence[0]);
        break;
    case 2:
        sentences = mediumsentence;
        numsentences = sizeof(mediumsentence) / sizeof(mediumsentence[0]);
        break;
    case 3:
        sentences = hardsentence;
        numsentences = sizeof(hardsentence) / sizeof(hardsentence[0]);
        break;
    default:
        printf("Invalid Level");
        exit(EXIT_FAILURE);
        break;
    }

     int index = rand() % numsentences;
    strncpy(sentence, sentences[index], max_sentence_length);
}

void saveresult(char sentence[max_sentence_length], float typingspeed, float accuracy){
    char filename[max_filename_length];
    printf("Enter A File Name:");
    scanf("%s", &filename);
    // Add ".txt" to the filename
    strcat(filename, ".txt");
    FILE *file=fopen(filename, "w");
    if (file==NULL)
    {
        perror("Error File");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "The Sentence: %s\n", sentence);
    fprintf(file, "Typing Speed: %.2f characters per second\n", typingspeed);
    fprintf(file, "Accuracy: %.2f%%\n", accuracy);
    fclose(file);
    printf("Results saved to", filename);
}