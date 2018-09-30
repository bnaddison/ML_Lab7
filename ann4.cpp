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

float hidden_node_error(float o, pair<float, float> we ) {
  //float error_sum = 0;
  float error_sum = we.first*we.second;

  float e = o*(1-o)*error_sum;

  return e;
}

float random_float() {
  float r = (float)rand()/(float)RAND_MAX;
  float ans = r * 2;
  return -1 + ans;
}


int main () {
  int count = 0;

  float w11 = random_float();
  float w12 = random_float();
  float w13 = random_float();

  float w21 = random_float();
  float w22 = random_float();
  float w23 = random_float();

  float w31 = random_float();
  float w32 = random_float();
  float w33 = random_float();

  float v1 = random_float();
  float v2 = random_float();
  float v3 = random_float();

  float n = 0.1f;
  float mse = 1;

  //cout << w11 << " " << w12 << " " << w13 << " " << w21 << " " << w22 << " " << w23 << endl;
  readfile("training examples");
  while (mse > 0.001f) {
    float temp_mse = 0;
    cout << "ITERATION: " << count << endl;
  for (int i = 0; i < training_examples.size(); i++) {
  //  cout << training_examples[i][0] << " " << training_examples[i][1] << " " << training_examples[i][2] << " " << training_examples[i][3] << endl;

    pair <float, float> x1n1(training_examples[i][0],w11);
    pair <float, float> x2n1(training_examples[i][1],w21);
    pair <float, float> x3n1(training_examples[i][2],w31);

    vector<pair<float,float> > node1;
    node1.push_back(x1n1);
    node1.push_back(x2n1);
    node1.push_back(x3n1);
    float n1 = node_output(node1);

    pair <float, float> x1n2(training_examples[i][0],w12);
    pair <float, float> x2n2(training_examples[i][1],w22);
    pair <float, float> x3n2(training_examples[i][2],w32);

    vector<pair<float,float> > node2;
    node2.push_back(x1n2);
    node2.push_back(x2n2);
    node2.push_back(x3n2);
    float n2 = node_output(node2);

    pair <float, float> x1n3(training_examples[i][0],w13);
    pair <float, float> x2n3(training_examples[i][1],w23);
    pair <float, float> x3n3(training_examples[i][2],w33);

    vector<pair<float,float> > node3;
    node3.push_back(x1n3);
    node3.push_back(x2n3);
    node3.push_back(x3n3);
    float n3 = node_output(node3);

    pair <float, float> n1o(n1,v1);
    pair <float, float> n2o(n2,v2);
    pair <float, float> n3o(n3,v3);

    vector<pair<float,float> > o_node;

    o_node.push_back(n1o);
    o_node.push_back(n2o);
    o_node.push_back(n3o);
    float output = node_output(o_node);
    cout << "Output: " << output <<  endl << "Target Output: " << training_examples[i][3] << endl;

    float o_error = output_node_error(output,training_examples[i][3]);

    cout << "Output Error: " << o_error << endl << endl;

    pair <float,float> v1o(v1,o_error);
    pair <float,float> v2o(v2,o_error);
    pair <float,float> v3o(v3,o_error);

    float n1_error = hidden_node_error(n1, v1o);
    float n2_error = hidden_node_error(n2, v2o);
    float n3_error = hidden_node_error(n3, v3o);
    //node.clear();

    v1+= n*o_error*n1;
    v2+= n*o_error*n2;
    v3+= n*o_error*n3;
    //cout << "v1: " << v1 << endl << "v2: " << v2 << endl << "v3: " << v3 << endl;

    //cout << "Hidden Node 1 Error: " << n1_error << endl << "Hidden Node 2 Error: " << n2_error << endl;

    w11+= n*n1_error*training_examples[i][0];
    w12+= n*n2_error*training_examples[i][0];
    w13+= n*n3_error*training_examples[i][0];
    w21+= n*n1_error*training_examples[i][1];
    w22+= n*n2_error*training_examples[i][1];
    w23+= n*n3_error*training_examples[i][1];
    w31+= n*n1_error*training_examples[i][2];
    w32+= n*n2_error*training_examples[i][2];
    w33+= n*n3_error*training_examples[i][2];

    //cout << "w11: " << w11 << endl << "w12: " << w12 << endl <<  "w13: " << w13 << endl << "w21: " << w21 << "w22: " << w22 << "w23: " << w23 << "w31: " << w31 << "w32: " << w32 << "w33: " << w33 << endl;
    temp_mse += pow((training_examples[i][3] - output),2);
  }
  mse = temp_mse/training_examples.size();
  cout << "MSE: " << mse << endl;
  count++;
}
}
