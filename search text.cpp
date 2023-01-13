#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

int main() {
    // Set up the text to search for
    string textToSearch = "text to search for";

    // Set up the folder path
    string folderPath = "path/to/folder";

    // Get the list of files in the folder
    vector<String> filenames;
    glob(folderPath + "/.", filenames);

    // Iterate through each file
    for (auto& filename : filenames) {
        // Read the image
        Mat image = imread(filename);

        // Convert the image to grayscale
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);

        // Perform text detection
        vector<Rect> boxes;
        Ptr<text::OCRTesseract> ocr = text::OCRTesseract::create();
        ocr->setWhiteList("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
        ocr->setLanguage("eng");
        ocr->run(gray, "", boxes, OCR_LEVEL_WORD);

        // Iterate through the detected text
        for (auto &box : boxes) {
            Mat roi(gray, box);
            string word = ocr->getUTF8Text();

            // Check if the text contains the text to search for
            if (word.find(textToSearch) != string::npos) {
                // Print the file name if the text is found
                cout << filename << endl;
                break;
            }
        }
    }

    return 0;
}
