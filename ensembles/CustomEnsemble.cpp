/*
Copyright (c) 2014, Qiangli Zhao and Yanhuang Jiang
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

* Neither the name of the copyright holders nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#include <vector>
using namespace std;
#include "Obj.h"
#include "DataSet.h"
#include "Classifier.h"
#include "Ensemble.h"
#include "CustomEnsemble.h"
using namespace libep;


const char	MyName[MAX_OBJECT_NAME_LENGTH]="CustomEnsemble";

CCustomEnsemble::CCustomEnsemble()
{
	Name=MyName;
}

//add a classifier to this ensemble
bool CCustomEnsemble::Add(CClassifier *Classifier,double Weight)
{
	Classifiers.push_back(Classifier);
	Weights.push_back(Weight);
	return true;
}
//remove a classifier from this ensemble
bool CCustomEnsemble::Remove(int ID)
{
	if((int)Classifiers.size()>ID)
		return false;

	Classifiers.erase(Classifiers.begin()+ID);
	Weights.erase(Weights.begin()+ID);
	return true;
}
