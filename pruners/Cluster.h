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

#ifndef CLUSTER_ENSPRUNER
#define CLUSTER_ENSPRUNER

namespace libedm
{
	class  CCluster: public CEnsemblePruner
	{
	public:
		typedef struct ParamStr
		{
			double Lamda;//threshold for a disagreement
		}ParamStr;

	public:
		CCluster(const CEnsemble &Ensemble,const CDataset &ValidatingSet,double Lamda=1.0);
		static CEnsemblePruner *Create(const CEnsemble &Ensemble,const CDataset &ValidatingSet,
			const void *UParams)
		{
			if(UParams==NULL)
				return new CCluster(Ensemble,ValidatingSet);

			const ParamStr *Param=(const ParamStr*)UParams;
			return new CCluster(Ensemble,ValidatingSet,Param->Lamda);
		}
		//predict a dataset
		CCluster(const CEnsemble &Ensemble,const CDataset &ValidatingSet,
			const vector<CPrediction*> &Predictions,double Lamda=1.0);
		static CEnsemblePruner *CreateOnPrediction(const CEnsemble &Ensemble,const CDataset &ValidatingSet,
			const vector<CPrediction*> &Predictions,const void *UParams)
		{
			if(UParams==NULL)
				return new CCluster(Ensemble,ValidatingSet,Predictions);

			const ParamStr *Param=(const ParamStr*)UParams;
			return new CCluster(Ensemble,ValidatingSet,Predictions,Param->Lamda);
		}

	private:
		typedef struct ClusterNodeStr
		{
			int Classifier;
			double Accuracy;
		}ClusterNodeStr;
		static bool AccuracyOrder(const ClusterNodeStr &a,const ClusterNodeStr &b)
		{
			return (a.Accuracy<b.Accuracy);
		}
		typedef vector<ClusterNodeStr> ClusterNodeArray;

	private:
		int k_mean(int m,const vector<CPrediction*> &Predictions,vector<ClusterNodeArray> &Clusters,vector<int> &Centers);
		double Theta(const vector<int> &V1,const vector<int> &V2,int Class1,int Class2);
		double kappa(const vector<int> &V1,const vector<int> &V2,int ClassNum);
	};
}

#endif

