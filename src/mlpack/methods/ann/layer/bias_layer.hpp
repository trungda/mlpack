/**
 * @file bias_layer.hpp
 * @author Marcus Edel
 *
 * Definition of the BiasLayer class, which implements a standard bias
 * layer.
 */
#ifndef __MLPACK_METHODS_ANN_LAYER_BIAS_LAYER_HPP
#define __MLPACK_METHODS_ANN_LAYER_BIAS_LAYER_HPP

#include <mlpack/core.hpp>
#include <mlpack/methods/ann/layer/layer_traits.hpp>
#include <mlpack/methods/ann/activation_functions/identity_function.hpp>

namespace mlpack {
namespace ann /** Artificial Neural Network. */ {

/**
 * An implementation of a standard bias layer with a default value of one.
 *
 * @tparam ActivationFunction Activation function used for the bias layer
 * (Default IdentityFunction).
 * @tparam DataType Type of data (arma::colvec, arma::mat or arma::sp_mat).
 */
template <
    class ActivationFunction = IdentityFunction,
    typename DataType = arma::colvec
>
class BiasLayer

{
 public:
  /**
   * Create the BiasLayer object using the specified number of bias units.
   *
   * @param layerSize The number of neurons.
   */
  BiasLayer(const size_t layerSize) :
      inputActivations(arma::ones<DataType>(layerSize)),
      delta(arma::zeros<DataType>(layerSize)),
      layerRows(layerSize),
      layerCols(1),
      layerSlices(1),
      outputMaps(1)
  {
    // Nothing to do here.
  }

  /**
   * Ordinary feed forward pass of a neural network, evaluating the function
   * f(x) by propagating the activity forward through f.
   *
   * @param inputActivation Input data used for evaluating the specified
   * activity function.
   * @param outputActivation Data to store the resulting output activation.
   */
  void FeedForward(const DataType& inputActivation, DataType& outputActivation)
  {
    ActivationFunction::fn(inputActivation, outputActivation);
  }

  /**
   * Ordinary feed backward pass of a neural network, calculating the function
   * f(x) by propagating x backwards trough f. Using the results from the feed
   * forward pass.
   *
   * @param inputActivation Input data used for calculating the function f(x).
   * @param error The backpropagated error.
   * @param delta The calculating delta using the partial derivative of the
   * error with respect to a weight.
   */
  void FeedBackward(const DataType& inputActivation,
                    const DataType& error,
                    DataType& delta)
  {
    DataType derivative;
    ActivationFunction::deriv(inputActivation, derivative);

    delta = error % derivative;
  }

  //! Get the input activations.
  const DataType& InputActivation() const { return inputActivations; }
  //! Modify the input activations.
  DataType& InputActivation() { return inputActivations; }

  //! Get the detla.
  DataType& Delta() const { return delta; }
  //! Modify the delta.
  DataType& Delta() { return delta; }

  //! Get input size.
  size_t InputSize() const { return layerRows; }
  //! Modify the delta.
  size_t& InputSize() { return layerRows; }

  //! Get output size.
  size_t OutputSize() const { return layerRows; }
  //! Modify the output size.
  size_t& OutputSize() { return layerRows; }

  //! Get the number of layer rows.
  size_t LayerRows() const { return layerRows; }
  //! Modify the number of layer rows.
  size_t& LayerRows() { return layerRows; }

  //! Get the number of layer columns.
  size_t LayerCols() const { return layerCols; }
  //! Modify the number of layer columns.
  size_t& LayerCols() { return layerCols; }

  //! Get the number of layer slices.
  size_t LayerSlices() const { return layerSlices; }

  //! Get the number of output maps.
  size_t OutputMaps() const { return outputMaps; }

  //! The the value of the deterministic parameter.
  bool Deterministic() const {return deterministic; }
  //! Modify the value of the deterministic parameter.
  bool& Deterministic() {return deterministic; }

 private:
  //! Locally-stored input activation object.
  DataType inputActivations;

  //! Locally-stored delta object.
  DataType delta;

  //! Locally-stored number of layer rows.
  size_t layerRows;

  //! Locally-stored number of layer cols.
  size_t layerCols;

  //! Locally-stored number of layer slices.
  size_t layerSlices;

  //! Locally-stored number of output maps.
  size_t outputMaps;

  //! Locally-stored deterministic parameter.
  bool deterministic;
}; // class BiasLayer

//! Layer traits for the bias layer.
template<typename ActivationFunction, typename DataType>
class LayerTraits<BiasLayer<ActivationFunction, DataType> >
{
 public:
  static const bool IsBinary = false;
  static const bool IsOutputLayer = false;
  static const bool IsBiasLayer = true;
  static const bool IsLSTMLayer = false;
};

}; // namespace ann
}; // namespace mlpack

#endif
