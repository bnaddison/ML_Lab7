// ADDBRA001 ML Lab 5

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <memory>
#include <string>
#include <math.h>

using namespace std;

vector < vector<float> > training_examples;

void readfile (string filename) {
  string line;
  ifstream in(filename);

  while (getline(in, line) ) {
    istringstream ss(line);

    string input1, input2, input3, output;

    ss >> input1 >> input2 >> input3 >> output;

    float x1 = stof(input1);
    float x2 = stof(input2);
    float x3 = stof(input3);
    float o = stof(output);

    vector<float> example = {x1,x2,x3,o};
    training_examples.push_back(example);
  }
}

float sigmoid (float net) {
  float o = 1/(1 + exp(-net) );
  return o;
}

float node_output(vector< pair<float,float> > inputs) {
  float output = 0;
  for (int i = 0; i < inputs.size(); i++) {
    output += inputs[i].first*inputs[i].second;
  }

  //output+=bias;

  float o = sigmoid(output);

  return o;

}


float output_node_error(float o, float t) {
  float e = o*(1-o)*(t-o);
  return e;
}

float hidden_node_error(float o, vector< pair<float, float> > we ) {
  float error_sum = 0;
  for (int i = 0; i < we.size(); i++) {
    error_sum += we[i].first*we[i].second;
  }
  float e = o*(1-o)*error_sum;

  return e;
}

float random_float() {
  float r = (float)rand()/(float)RAND_MAX;
  float ans = r * 0.8f;
  return r + 0.2f;
}


int main () {

  float w11 = random_float();
  float w12 = random_float();
  float w13 = random_float();

  float w21 = random_float();
  float w22 = random_float();
  float w23 = random_float();

  float w31 = random_float();
  float w32 = random_float();
  float w33 = random_float();

  cout << w11 << " " << w12 << " " << w13 << " " << w21 << " " << w22 << " " << w23 << endl;
  readfile("training examples");
  for (int i = 0; i < training_examples.size(); i++) {
    cout << training_examples[i][0] << " " << training_examples[i][1] << " " << training_examples[i][2] << " " << training_examples[i][3] << endl;

    pair <float, float> x1n1(training_examples[i][0],w11);
    pair <float, float> x2n1(training_examples[i][1],w21);
    pair <float, float> x3n1(training_examples[i][2],w31);

    node1.push_back(x1n1);
    node1.push_back(x2n1);
    node1.push_back(x3n1);

    float n1 = node_output(node1);

    pair <float, float> x1n2(training_examples[i][0],w12);
    pair <float, float> x2n2(training_examples[i][1],w22);
    pair <float, float> x3n2(training_examples[i][2],w32);

    node2.push_back(x1n2);
    node2.push_back(x2n2);
    node2.push_back(x3n2);
    float n1 = node_output(node2);

    pair <float, float> x1n3(training_examples[i][0],w13);
    pair <float, float> x2n3(training_examples[i][1],w23);
    pair <float, float> x3n3(training_examples[i][2],w33);

    node.push_back(x1n1);
    node.push_back(x2n1);
    float n1 = node_output(node);
  }
}
