# systemc-opencv-project

systemc opencv guide 
-

Let's walk through the entire process of creating a SystemC project that reads an image, applies a black and white filter, applies a custom filter, and displays both the original and processed images using OpenCV. This tutorial will cover everything from setting up your environment to writing and running the code.

Step 1: Setting Up Your Environment
-

Install SystemC:

Download SystemC from the Accellera website.

Follow the installation instructions provided in the SystemC documentation.

Install OpenCV:

Download OpenCV from the OpenCV website.

Follow the installation instructions provided in the OpenCV documentation.

Set Up Your Project Directory:

Create a directory for your project. For example, systemc_opencv_project.

Inside this directory, create two subdirectories: src for source files and include for header files.


Step 2: Writing the Code
-


Image Processor Module (image_processor.cpp)
Create a file named image_processor.cpp in the src directory and add the following code:

cpp
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
                cv::Mat kernel = (cv::Mat_<float>(1, 2) << -1, 0);
                cv::filter2D(gray_image, custom_filtered_image, -1, kernel);

                // Display the processed images
                cv::imshow("Black and White Image", gray_image);
                cv::imshow("Custom Filtered Image", custom_filtered_image);
                cv::waitKey(0); // Wait for a key press to close the windows
            } else {
                std::cerr << "Error loading the image." << std::endl;
            }
        }
    }

    SC_CTOR(ImageProcessor) {
        SC_THREAD(process);
        sensitive << clk.pos();
    } 
    };


Main File (main.cpp)

Create a file named main.cpp in the src directory and add the following code:

cpp

#include <systemc.h>
#include "image_processor.cpp" // Include the ImageProcessor module
int sc_main(int argc, char* argv[]) { sc_clock clk("clk", 10, SC_NS);
    sc_signal<bool> reset;
    
    ImageProcessor image_processor("image_processor");
    image_processor.clk(clk);
    image_processor.reset(reset);
    
    // Simulation
    sc_start(0, SC_NS);
    reset.write(false);
    sc_start(10, SC_NS);
    reset.write(true);
    sc_start(10, SC_NS);
    reset.write(false);
    sc_start(100, SC_NS);

    return 0;}

Step 3: Creating the Makefile
-

Create a file named Makefile in the root directory of your project and add the following code:

makefile
CXX = g++
CXXFLAGS = -I/usr/local/include/opencv4 -I$(SYSTEMC_HOME)/include -Wno-unused-variable -Wno-sign-compare -Wno-maybe-uninitialized
LDFLAGS = -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_imgproc -lopencv_highgui -L$(SYSTEMC_HOME)/lib-linux64 -lsystemc

all: main

main: main.o image_processor.o
    $(CXX) -o main main.o image_processor.o $(LDFLAGS)

main.o: src/main.cpp
    $(CXX) $(CXXFLAGS) -c src/main.cpp

image_processor.o: src/image_processor.cpp
    $(CXX) $(CXXFLAGS) -c src/image_processor.cpp

clean:
    rm -f *.o main

    
Step 4: Compiling and Running the Project
-

Compile the Project:

Open a terminal and navigate to your project directory.

Run the following command to compile the project:

sh
make
Run the Executable:

Ensure that the image file image.jpg is in the same directory as your executable.

Run the executable:

sh
./main

Step 5: Observing the Output
-

The program will display three windows:

Original Image: Shows the original image.

Black and White Image: Shows the image after applying the black and white filter.

Custom Filtered Image: Shows the image after applying the custom filter with the kernel [-1, 0].

Press any key to close the windows.


You've successfully created a SystemC project that integrates with OpenCV to read, process, and display images. This tutorial covered setting up the environment, writing the code, creating a Makefile, and running the project.

feel free to mail me on :

dagmazen@gmail.com
-

full installation guide (read installation_tutorial.pdf on repository)
-
