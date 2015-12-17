#include "math.hpp"
#include "network.hpp"
#include "loaders.hpp"
#include "functions.hpp"
#include "statistics.hpp"



/////////////////////////////////////////////////////////
///             parameters to play with               ///
/////////////////////////////////////////////////////////

// načíst textová nebo bitmapová data
const bool load_bitmap_data = false;

// složka kde se nachásí vstupní data (buď "duplicated", nebo "normal")
const auto input_folder = "duplicated";

/////////////////////////////////////////////////////////
///             parameters to play with               ///
/////////////////////////////////////////////////////////



// parametry backpropagation, netřeba měnit
const uint epochs = 800;     // pačet iteraci
const uint batch_size = 10;  // velikost mini batche
const Scalar eta = 0.01;     // rychlost učení
const Scalar lambda = 0.0;   // weight decay
const bool use_advanced_weight_initializer = true;

// složka, kam se maji uložit soubory popisující průběh učení (veličiny accurancy a cost function)
const auto output_folder = "out";

// velikost sítě pro textový a bitmapový vstup
const std::vector<uint> shape_txt = {9, 9, 3};
const std::vector<uint> shape_bmp = {121, 9, 3};

// pokud nebudete zkoušet vstup na bitmapách o velikosti 14x14 tak není třeba měnit 
const uint variants = 1;




int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    // create multilayered neural net with sigmoid activation function and quadratic cost function
    Network<Fast_sigmoid, Quadratic_cost> network(load_bitmap_data ? shape_bmp : shape_txt);

    // load data sets
    auto data_sets = load_bitmap_data ? load_bmp(input_folder) : load_txt(input_folder);

    // initialize weights
    if (use_advanced_weight_initializer)
        network.init_2(gen);
    else
        network.init(gen);

    // run stochastics gradient descend
    auto statistics = network.sgd(data_sets.training, epochs, batch_size, eta, lambda, gen, data_sets.validation);
    save_statistics(statistics, output_folder);


    std::cout << std::endl;
    std::cout << "///////////////////////////////////////////////////" << std::endl;
    std::cout << "//                    Results:                  ///" << std::endl;
    std::cout << "///////////////////////////////////////////////////" << std::endl << std::endl;

    std::cout << "accurancy: " << network.accurancy(data_sets.testing) << std::endl << std::endl;
    std::cout << "confusion matrix" << std::endl << network.confusion(data_sets.testing) << std::endl;

    return 0;
}
