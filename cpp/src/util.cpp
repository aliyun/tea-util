// This file is auto-generated, don't edit it. Thanks.

#include <darabonba/util.hpp>
#include <boost/any.hpp>
#include <boost/exception/all.hpp>
#include <darabonba/core.hpp>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace Darabonba;
using namespace std;

vector<int> Darabonba_Util::Client::toBytes(string val){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

string Darabonba_Util::Client::toString(vector<int> val){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

boost::any Darabonba_Util::Client::parseJSON(string val){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

vector<int> Darabonba_Util::Client::readAsBytes(ofstream stream){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

string Darabonba_Util::Client::readAsString(ofstream stream){
  vector<int> buff = Client::readAsBytes(stream);
  return Client::toString(buff);
}

boost::any Darabonba_Util::Client::readAsJSON(ofstream stream){
  return Client::parseJSON(Client::readAsString(stream));
}

string Darabonba_Util::Client::getNonce(){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

string Darabonba_Util::Client::getDateUTCString(){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

string Darabonba_Util::Client::defaultString(string real, string default){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

int Darabonba_Util::Client::defaultNumber(int real, int default){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

string Darabonba_Util::Client::toFormString(map<string, boost::any> val){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

string Darabonba_Util::Client::toJSONString(boost::any val){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

bool Darabonba_Util::Client::empty(string val){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

bool Darabonba_Util::Client::equalString(string val1, string val2){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

bool Darabonba_Util::Client::equalNumber(int val1, int val2){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

bool Darabonba_Util::Client::isUnset(boost::any value){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

map<string, string> Darabonba_Util::Client::stringifyMapValue(map<string, boost::any> m){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

map<string, boost::any> Darabonba_Util::Client::anyifyMapValue(map<string, string> m){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

bool Darabonba_Util::Client::assertAsBoolean(boost::any value){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

string Darabonba_Util::Client::assertAsString(boost::any value){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

vector<int> Darabonba_Util::Client::assertAsBytes(boost::any value){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

int Darabonba_Util::Client::assertAsNumber(boost::any value){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

map<string, boost::any> Darabonba_Util::Client::assertAsMap(boost::any value){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

string Darabonba_Util::Client::getUserAgent(string userAgent){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

bool Darabonba_Util::Client::is2xx(int code){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

bool Darabonba_Util::Client::is3xx(int code){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

bool Darabonba_Util::Client::is4xx(int code){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

bool Darabonba_Util::Client::is5xx(int code){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

void Darabonba_Util::Client::validateModel(Model m){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

map<string, boost::any> Darabonba_Util::Client::toMap(Model in){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

void Darabonba_Util::Client::sleep(int millisecond){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

vector<map<string, boost::any>> Darabonba_Util::Client::toArray(boost::any input){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

ofstream Darabonba_Util::Client::assertAsReadable(boost::any value){
  BOOST_THROW_EXCEPTION(boost::exception('Un-implemented');
}

