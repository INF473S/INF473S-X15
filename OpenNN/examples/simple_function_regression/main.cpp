/****************************************************************************************************************/
/*                                                                                                              */
/*   OpenNN: Open Neural Networks Library                                                                       */
/*   www.artelnics.com/opennn                                                                                   */
/*                                                                                                              */
/*   S I M P L E   F U N C T I O N   R E G R E S S I O N   A P P L I C A T I O N                                */
/*                                                                                                              */
/*   Roberto Lopez                                                                                              */
/*   Artelnics - Making intelligent use of data                                                                 */
/*   robertolopez@artelnics.com                                                                                 */
/*                                                                                                              */
/****************************************************************************************************************/

// This is a function regression problem. 

// System includes

#include <iostream>
#include <sstream>
#include <time.h>
#include <stdexcept>

// OpenNN includes

#include "../../opennn/opennn.h"

using namespace OpenNN;

int main(void)
{
    try
    {
        int rank = 0;

#ifdef __OPENNN_MPI__

        int size = 1;

        MPI_Init(NULL,NULL);

        MPI_Comm_size(MPI_COMM_WORLD, &size);

        MPI_Comm_rank(MPI_COMM_WORLD, &rank);

#endif

        if(rank == 0)
        {
            std::cout << "OpenNN. Simple Function Regression Application." << std::endl;
        }

        srand( (unsigned)time( NULL ) );

        // Global variables

        DataSet data_set;

		std::string path = "C:\\Users\\Romain Loiseau\\Documents\\Mes_documents\\X\\2A\\Modal_SAMSON\\GIT\\OpenNN\\examples\\simple_function_regression\\data\\";
		
		Vector<int> architecture(3);
		architecture[0] = 32;
		architecture[1] = 1;
		architecture[2] = 1;
		MultilayerPerceptron mlp = MultilayerPerceptron(architecture);

		NeuralNetwork neural_network = NeuralNetwork(mlp);

        LossIndex loss_index;

        TrainingStrategy training_strategy;

        // Local variables

        DataSet local_data_set;

        NeuralNetwork local_neural_network;

        LossIndex local_loss_index;

        TrainingStrategy local_training_strategy;

        // Data set

        if(rank == 0)
        {
            data_set.set_data_file_name(path+"Size_32_Step_1_short.dat");
			data_set.set_header_line(true);
            data_set.load_data();

            Variables* variables_pointer = data_set.get_variables_pointer();

            variables_pointer->set_use(0, Variables::Input);
			variables_pointer->set_use(1, Variables::Input);
			variables_pointer->set_use(2, Variables::Input);
			variables_pointer->set_use(3, Variables::Input);
			variables_pointer->set_use(4, Variables::Input);
			variables_pointer->set_use(5, Variables::Input);
			variables_pointer->set_use(6, Variables::Input);
			variables_pointer->set_use(7, Variables::Input);
			variables_pointer->set_use(8, Variables::Input);
			variables_pointer->set_use(9, Variables::Input);
			variables_pointer->set_use(10, Variables::Input);
			variables_pointer->set_use(11, Variables::Input);
			variables_pointer->set_use(12, Variables::Input);
			variables_pointer->set_use(13, Variables::Input);
			variables_pointer->set_use(14, Variables::Input);
			variables_pointer->set_use(15, Variables::Input);
			variables_pointer->set_use(16, Variables::Input);
			variables_pointer->set_use(17, Variables::Input);
			variables_pointer->set_use(18, Variables::Input);
			variables_pointer->set_use(19, Variables::Input);
			variables_pointer->set_use(20, Variables::Input);
			variables_pointer->set_use(21, Variables::Input);
			variables_pointer->set_use(22, Variables::Input);
			variables_pointer->set_use(23, Variables::Input);
			variables_pointer->set_use(24, Variables::Input);
			variables_pointer->set_use(25, Variables::Input);
			variables_pointer->set_use(26, Variables::Input);
			variables_pointer->set_use(27, Variables::Input);
			variables_pointer->set_use(28, Variables::Input);
			variables_pointer->set_use(29, Variables::Input);
			variables_pointer->set_use(30, Variables::Input);
			variables_pointer->set_use(31, Variables::Input);

			
			variables_pointer->set_use(42, Variables::Target);
		

            Matrix<std::string> inputs_information = variables_pointer->arrange_inputs_information();
            Matrix<std::string> targets_information = variables_pointer->arrange_targets_information();
			
            Instances* instances_pointer = data_set.get_instances_pointer();

            instances_pointer->set_training();

            Vector< Statistics<double> > inputs_statistics = data_set.scale_inputs_minimum_maximum();
            Vector< Statistics<double> > targets_statistics = data_set.scale_targets_minimum_maximum();

            // Neural network

            Inputs* inputs_pointer = neural_network.get_inputs_pointer();
            inputs_pointer->set_information(inputs_information);

            Outputs* outputs_pointer = neural_network.get_outputs_pointer();
            outputs_pointer->set_information(targets_information);

            neural_network.construct_scaling_layer();
            ScalingLayer* scaling_layer_pointer = neural_network.get_scaling_layer_pointer();
            scaling_layer_pointer->set_statistics(inputs_statistics);
			scaling_layer_pointer->set_scaling_method(ScalingLayer::MinimumMaximum);
			

            neural_network.construct_unscaling_layer();
            UnscalingLayer* unscaling_layer_pointer = neural_network.get_unscaling_layer_pointer();
            unscaling_layer_pointer->set_statistics(targets_statistics);
            unscaling_layer_pointer->set_unscaling_method(UnscalingLayer::MinimumMaximum);

            // Loss index

            loss_index.set_data_set_pointer(&data_set);
            loss_index.set_neural_network_pointer(&neural_network);

            // Training strategy

            training_strategy.set(&loss_index);

            QuasiNewtonMethod* quasi_Newton_method_pointer = training_strategy.get_quasi_Newton_method_pointer();

            quasi_Newton_method_pointer->set_minimum_loss_increase(1.0e-3);
			quasi_Newton_method_pointer->set_maximum_time(36000);
        }

#ifdef __OPENNN_MPI__
        MPI_Barrier(MPI_COMM_WORLD);

        local_data_set.set_MPI(&data_set);

        local_neural_network.set_MPI(&neural_network);

        local_loss_index.set_MPI(&local_data_set,&local_neural_network,&loss_index);

        local_training_strategy.set_MPI(&local_loss_index,&training_strategy);

        MPI_Barrier(MPI_COMM_WORLD);

        TrainingStrategy::Results training_strategy_results = local_training_strategy.perform_training();
#else
        TrainingStrategy::Results training_strategy_results = training_strategy.perform_training();
#endif

        if(rank == 0)
        {
#ifdef __OPENNN_MPI__
            neural_network.set_multilayer_perceptron_pointer(local_neural_network.get_multilayer_perceptron_pointer());
#endif
            // Testing analysis

            Instances* instances_pointer = data_set.get_instances_pointer();

            instances_pointer->set_testing();

            TestingAnalysis testing_analysis(&neural_network, &data_set);

			TestingAnalysis::LinearRegressionResults linear_regression_results = testing_analysis.perform_linear_regression_analysis();

            // Save results

            ScalingLayer* scaling_layer_pointer = neural_network.get_scaling_layer_pointer();
            UnscalingLayer* unscaling_layer_pointer = neural_network.get_unscaling_layer_pointer();

            scaling_layer_pointer->set_scaling_method(ScalingLayer::MinimumMaximum);
            unscaling_layer_pointer->set_unscaling_method(UnscalingLayer::MinimumMaximum);

            data_set.save("C:\\Users\\Romain Loiseau\\Documents\\Mes_documents\\X\\2A\\Modal_SAMSON\\GIT\\OpenNN\\examples\\simple_function_regression\\data\\data_set.xml");

            neural_network.save("C:\\Users\\Romain Loiseau\\Documents\\Mes_documents\\X\\2A\\Modal_SAMSON\\GIT\\OpenNN\\examples\\simple_function_regression\\data\\neural_network.xml");
            neural_network.save_expression("C:\\Users\\Romain Loiseau\\Documents\\Mes_documents\\X\\2A\\Modal_SAMSON\\GIT\\OpenNN\\examples\\simple_function_regression\\data\\expression.txt");

            loss_index.save("C:\\Users\\Romain Loiseau\\Documents\\Mes_documents\\X\\2A\\Modal_SAMSON\\GIT\\OpenNN\\examples\\simple_function_regression\\data\\loss_index.xml");

            training_strategy.save("C:\\Users\\Romain Loiseau\\Documents\\Mes_documents\\X\\2A\\Modal_SAMSON\\GIT\\OpenNN\\examples\\simple_function_regression\\data\\training_strategy.xml");
            training_strategy_results.save("C:\\Users\\Romain Loiseau\\Documents\\Mes_documents\\X\\2A\\Modal_SAMSON\\GIT\\OpenNN\\examples\\simple_function_regression\\data\\training_strategy_results.dat");

			linear_regression_results.save("C:\\Users\\Romain Loiseau\\Documents\\Mes_documents\\X\\2A\\Modal_SAMSON\\GIT\\OpenNN\\examples\\simple_function_regression\\data\\linear_regression_analysis_results.dat");
        }

#ifdef __OPENNN_MPI__

        MPI_Barrier(MPI_COMM_WORLD);

        MPI_Finalize();

#endif
        return(0);
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;

        return(1);
    }
}  


// OpenNN: Open Neural Networks Library.
// Copyright (C) 2005-2015 Roberto Lopez
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
