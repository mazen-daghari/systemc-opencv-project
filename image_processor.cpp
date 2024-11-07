#include <systemc.h>
#include <opencv2/opencv.hpp>

SC_MODULE(ImageProcessor) {
    sc_in<bool> clk;
    sc_in<bool> reset;

    void process() {
        while (true) {
            wait(); // Wait for clock edge
            if (reset.read() == true) {
                std::cout << "Reset signal received" << std::endl;
                continue;
            }

            cv::Mat image = cv::imread("image.jpg", cv::IMREAD_COLOR); // Load the image in color

            if (!image.empty()) { // Check if the image was loaded correctly
                cv::imshow("Original Image", image); // Display the original image

                cv::Mat gray_image;
                cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY); // Convert to black and white

                // Apply custom filter
                cv::Mat custom_filtered_image;
                cv::Mat kernel = (cv::Mat_<float>(1, 2) << 1, -1);
                cv::filter2D(gray_image, custom_filtered_image, -1, kernel);

                // Display the processed images
                cv::imshow("Black and White Image", gray_image);
                cv::imshow("Custom Filtered Image", custom_filtered_image);
                cv::waitKey(0); // Wait for a key press to close the windows
            }
            else {
                std::cerr << "Error loading the image." << std::endl;
            }
        }
    }

    SC_CTOR(ImageProcessor) {
        SC_THREAD(process);
        sensitive << clk.pos();
    }
};
