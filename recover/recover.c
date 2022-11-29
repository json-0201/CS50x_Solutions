#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Define a data type for readability
typedef uint8_t BYTE;

// Define block size
int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Command line argument input number: 1
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Forensic image cannot be opened
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Forensic image cannot be opened for reading\n");
        return 1;
    }

    // Initialize buffer
    BYTE buffer[BLOCK_SIZE];
    // Initialize jpeg output pointer
    FILE *jpeg = NULL;
    // Initialize counter
    int counter = 0;
    // Initialize string for filename
    char filename[8]; // String array for JPEG files

    // Loop through every 512-byte block of card (BLOCK_SIZE many 1-byte memory)
    while (fread(buffer, 1, BLOCK_SIZE, card) == BLOCK_SIZE)
    {
        // JPEG header check
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            // If first JPEG file
            if (counter == 0)
            {
                sprintf(filename, "%03i.jpg", counter); // Save filename in string format -> %03i = "00i.jpg"
                // Open first jpeg pointer to save buffer
                jpeg = fopen(filename, "w");

                // Write the header block to jpeg output pointer
                fwrite(buffer, 1, BLOCK_SIZE, jpeg);
                counter++; // Initial increment
            }

            else
            {
                // Close the previous file when new JPEG header block detected
                fclose(jpeg);

                sprintf(filename, "%03i.jpg", counter); // Update incremented filename
                // Open new jpeg pointer to save buffer
                jpeg = fopen(filename, "w");

                // Write the header block to jpeg output pointer
                fwrite(buffer, 1, BLOCK_SIZE, jpeg);
                counter++; // Increment counter
            }
        }

        else
        {
            // If jpeg output pointer is not closed (JPEG is found and past its header block)
            if (jpeg != NULL)
            {
                fwrite(buffer, 1, BLOCK_SIZE, jpeg);
            }
        }
    }

    // Free memory used for FILE pointers
    fclose(card);
    fclose(jpeg);
}