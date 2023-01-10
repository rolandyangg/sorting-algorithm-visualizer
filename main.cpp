#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <array>
#include <filesystem>

int main()
{
    float width = 1280;
    float height = 720;

    /**
     0 = Bubble Sort
     1 = Bogo Sort
     */
    std::string sortName = "Bogo Sort";
    int sortType = 1;

    sf::RenderWindow window(sf::VideoMode(width, height), sortName);
    window.setFramerateLimit(0);

    const int numBlocks = 6;
    float blockWidth = width / numBlocks;
    float blockHeight = height / numBlocks;

    // instantiate variables
    int i = 0;
    int j = 0;
    int greenIndex = 0;
    int accessed[2] = { -1, -1 }; // Set to -1 to avoid undefined behavior
    int comparisons = 0;
    bool isSorted = false;

    // randomly sort the blocks
    int arr[numBlocks];
    for (int i = 1; i <= numBlocks; i++)
        arr[i - 1] = i;
    std::random_device device;
    std::mt19937 g(device());
    std::shuffle(arr, arr + numBlocks, g);

    // setup text sprite
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text comparisonsText;
    comparisonsText.setFont(font);
    comparisonsText.setString("comparisons: " + std::to_string(comparisons));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        switch (sortType) {
            case 0: // bubble sort
                if (!isSorted) {
                    if (i < numBlocks - 1) {
                        if (j < numBlocks - i - 1) {
                            accessed[0] = arr[j];
                            accessed[1] = arr[j + 1];
                            if (arr[j] > arr[j + 1]) {
                                int temp = arr[j];
                                arr[j] = arr[j + 1];
                                arr[j + 1] = temp;
                            }
                            comparisons++;
                            j++;
                        }
                        else {
                            i++;
                            j = 0;
                        }
                        comparisons++;
                    } else {
                        isSorted = true;
                    }
                    comparisons++;
                }
                else {
                    if (greenIndex != numBlocks)
                        greenIndex++;
                }
                break;
            case 1: // bogo sort
                if (!isSorted) {
                    if (i < numBlocks - 1) {
                        accessed[0] = arr[i];
                        accessed[1] = arr[i + 1];
                        if (arr[i] > arr[i + 1]) {
                            std::shuffle(arr, arr + numBlocks, g);
                            i = 0;
                        } else {
                            i++;
                        }
                        comparisons++;
                    } else {
                        isSorted = true;
                    }
                    comparisons++;
                }
                else {
                    if (greenIndex != numBlocks)
                        greenIndex++;
                }
                break;
        }

        // render
        window.clear(sf::Color::Black);

        for (int z = 0; z < numBlocks; z++) {
            sf::RectangleShape rectangle(sf::Vector2f(blockWidth, blockHeight * arr[z]));
            rectangle.setPosition(z * blockWidth, height - (blockHeight * arr[z]));

            // set colors of rectangles
            if (isSorted && z < greenIndex) {
                rectangle.setFillColor(sf::Color::Green);
            }
            else if (accessed[0] == z || accessed[1] == z)
                rectangle.setFillColor(sf::Color::Red);


            window.draw(rectangle);
        }

        // update num comparisons
        comparisonsText.setString("comparisons: " + std::to_string(comparisons));
        window.draw(comparisonsText);

        window.display();
    }

    return 0;
}
