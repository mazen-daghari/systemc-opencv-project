#include <systemc.h>
#include "image_processor.cpp" // Include the ImageProcessor module

int sc_main(int argc, char* argv[]) {
    sc_clock clk("clk", 10, SC_NS);
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

    return 0;
}
