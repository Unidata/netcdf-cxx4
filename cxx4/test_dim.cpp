// Purpose: Converts ida3 format xma data to netcdf4
// Usage:   xma2netcdf <shot number>


#include <iostream>
#include <ncFile.h>
#include <ncDim.h>
#include <ncException.h>
#include <iomanip>
#include <netcdf>
using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;


int main()
{
  try
    {
      cout<<"Opening file \"firstFile.cdf\" with NcFile::replace"<<endl;
      NcFile ncFile("firstFile.cdf", NcFile::replace);

      cout<<left<<setw(55)<<"Testing addGroup(\"groupName\")";
      NcGroup groupA(ncFile.addGroup("groupA"));
      NcGroup groupA0(ncFile.addGroup("groupA0"));
      NcGroup groupB(groupA.addGroup("groupB"));
      NcGroup groupC(groupA.addGroup("groupC"));
      cout <<"    -----------   passed\n";

      cout <<left<<setw(55)<<"Testing addDim(\"dimensionName\")";
      NcDim dim1 = ncFile.addDim("dim1",11);
      NcDim dim2 = ncFile.addDim("dim2");
      NcDim dim3 = ncFile.addDim("dim3",13);
      NcDim dim4 = groupB.addDim("dim4",14);
      NcDim dim5 = groupB.addDim("dim5",15);
      NcDim dim6 = groupB.addDim("dim6",16);
      NcDim dim7 = groupB.addDim("dim7",17);
      cout <<"    -----------   passed\n";

      cout <<left<<setw(55)<<"Testing addVar(\"dimensionName\")";
      // Coordinate variables
      NcVar var1 = ncFile.addVar("dim1", NcInt{});
      NcVar var4 = groupB.addVar("dim4", NcInt{});
      cout <<"    -----------   passed\n";

      cout <<left<<setw(55)<<"Testing NcDim::isUnlimited()";
      if( dim1.isUnlimited())    throw NcException("Error in test 1.1",__FILE__,__LINE__);
      if( !dim2.isUnlimited())   throw NcException("Error in test 1.2",__FILE__,__LINE__);
      if( dim3.isUnlimited())    throw NcException("Error in test 1.3",__FILE__,__LINE__);
      if( dim4.isUnlimited())    throw NcException("Error in test 1.4",__FILE__,__LINE__);
      if( dim5.isUnlimited())    throw NcException("Error in test 1.5",__FILE__,__LINE__);
      if( dim6.isUnlimited())    throw NcException("Error in test 1.6",__FILE__,__LINE__);
      if( dim7.isUnlimited())    throw NcException("Error in test 1.7",__FILE__,__LINE__);
      cout <<"    -----------   passed\n";

     cout <<left<<setw(55)<<"Testing NcDim::isNull()";
     if( dim1.isNull())    throw NcException("Error in test 2.1",__FILE__,__LINE__);
     NcDim tmpDim;
     if( !tmpDim.isNull()) throw NcException("Error in test 2.2",__FILE__,__LINE__);
      cout <<"    -----------   passed\n";

     cout <<left<<setw(55)<<"Testing NcDim::getSize()";
     if( dim1.getSize() != 11)    throw NcException("Error in test 3.1",__FILE__,__LINE__);
     if( dim2.getSize() != 0 )    throw NcException("Error in test 3.2",__FILE__,__LINE__);
     if( dim3.getSize() != 13)    throw NcException("Error in test 3.3",__FILE__,__LINE__);
     if( dim4.getSize() != 14)    throw NcException("Error in test 3.4",__FILE__,__LINE__);
     if( dim5.getSize() != 15)    throw NcException("Error in test 3.5",__FILE__,__LINE__);
     if( dim6.getSize() != 16)    throw NcException("Error in test 3.6",__FILE__,__LINE__);
     if( dim7.getSize() != 17)    throw NcException("Error in test 3.7",__FILE__,__LINE__);
     cout <<"    -----------   passed\n";

     cout <<left<<setw(55)<<"Testing NcDim::getParentGroup()";
     if( !(dim1.getParentGroup() == ncFile))   throw NcException("Error in test 4.1",__FILE__,__LINE__);
     if( !(dim2.getParentGroup() == ncFile))   throw NcException("Error in test 4.2",__FILE__,__LINE__);
     if( !(dim3.getParentGroup() == ncFile))   throw NcException("Error in test 4.3",__FILE__,__LINE__);
     if( !(dim4.getParentGroup() == groupB))   throw NcException("Error in test 4.4",__FILE__,__LINE__);
     if( !(dim5.getParentGroup() == groupB))   throw NcException("Error in test 4.5",__FILE__,__LINE__);
     if( !(dim6.getParentGroup() == groupB))   throw NcException("Error in test 4.6",__FILE__,__LINE__);
     if( !(dim7.getParentGroup() == groupB))   throw NcException("Error in test 4.7",__FILE__,__LINE__);
     cout <<"    -----------   passed\n";

     cout <<left<<setw(55)<<"Testing NcDim::getName()";
     if( dim1.getName() != "dim1")   throw NcException("Error in test 5.1",__FILE__,__LINE__);
     if( dim2.getName() != "dim2")   throw NcException("Error in test 5.2",__FILE__,__LINE__);
     if( dim3.getName() != "dim3")   throw NcException("Error in test 5.3",__FILE__,__LINE__);
     if( dim4.getName() != "dim4")   throw NcException("Error in test 5.4",__FILE__,__LINE__);
     if( dim5.getName() != "dim5")   throw NcException("Error in test 5.5",__FILE__,__LINE__);
     if( dim6.getName() != "dim6")   throw NcException("Error in test 5.6",__FILE__,__LINE__);
     if( dim7.getName() != "dim7")   throw NcException("Error in test 5.7",__FILE__,__LINE__);
     cout <<"    -----------   passed\n";





      cout <<left<<setw(55)<<"Testing NcGroup::getDimCount([netCDF::Location])";
      if( ncFile.getDimCount() != 3)                           throw NcException("Error in test 6.1",__FILE__,__LINE__);
      if( ncFile.getDimCount(NcGroup::Current) != 3)           throw NcException("Error in test 6.2",__FILE__,__LINE__);
      if( ncFile.getDimCount(NcGroup::All) != 7)               throw NcException("Error in test 6.3",__FILE__,__LINE__);
      if( ncFile.getDimCount(NcGroup::Parents) != 0)           throw NcException("Error in test 6.4",__FILE__,__LINE__);
      if( ncFile.getDimCount(NcGroup::Children) != 4)          throw NcException("Error in test 6.5",__FILE__,__LINE__);
      if( ncFile.getDimCount(NcGroup::ParentsAndCurrent) != 3) throw NcException("Error in test 6.6",__FILE__,__LINE__);
      if( ncFile.getDimCount(NcGroup::ChildrenAndCurrent) != 7)throw NcException("Error in test 6.7",__FILE__,__LINE__);
      if( groupA.getDimCount() != 0)                           throw NcException("Error in test 6.8",__FILE__,__LINE__);
      if( groupA.getDimCount(NcGroup::Current) != 0)           throw NcException("Error in test 6.9",__FILE__,__LINE__);
      if( groupA.getDimCount(NcGroup::All) != 7)               throw NcException("Error in test 6.10",__FILE__,__LINE__);
      if( groupA.getDimCount(NcGroup::Parents) != 3)           throw NcException("Error in test 6.11",__FILE__,__LINE__);
      if( groupA.getDimCount(NcGroup::Children) != 4)          throw NcException("Error in test 6.12",__FILE__,__LINE__);
      if( groupA.getDimCount(NcGroup::ParentsAndCurrent) != 3) throw NcException("Error in test 6.13",__FILE__,__LINE__);
      if( groupA.getDimCount(NcGroup::ChildrenAndCurrent) != 4)throw NcException("Error in test 6.14",__FILE__,__LINE__);
      cout <<"    -----------   passed\n";



      cout <<left<<setw(55)<<"Testing NcGroup::getDims([netCDF::Location])";
      {
	multimap<string,NcDim> dimMap;
	multimap<string,NcDim>::iterator iter;

	// operations on ncFile

	dimMap = ncFile.getDims();
	if( dimMap.size() != 3)        throw NcException("Error in test 7.1",__FILE__,__LINE__);
	iter=dimMap.find("dim1");
	if( iter == dimMap.end())    throw NcException("Error in test 7.2",__FILE__,__LINE__);
	iter=dimMap.find("dim2");
	if( iter == dimMap.end())    throw NcException("Error in test 7.3",__FILE__,__LINE__);
	iter=dimMap.find("dim3");
	if( iter == dimMap.end())    throw NcException("Error in test 7.4",__FILE__,__LINE__);

	dimMap = ncFile.getDims(NcGroup::Current);
	if( dimMap.size() != 3)        throw NcException("Error in test 7.5",__FILE__,__LINE__);
	iter=dimMap.find("dim1");
	if( iter == dimMap.end())    throw NcException("Error in test 7.6",__FILE__,__LINE__);
	iter=dimMap.find("dim2");
	if( iter == dimMap.end())    throw NcException("Error in test 7.7",__FILE__,__LINE__);
	iter=dimMap.find("dim3");
	if( iter == dimMap.end())    throw NcException("Error in test 7.8",__FILE__,__LINE__);

	dimMap = ncFile.getDims(NcGroup::Parents);
	if( dimMap.size() != 0)        throw NcException("Error in test 7.9",__FILE__,__LINE__);

	dimMap = ncFile.getDims(NcGroup::Children);
	if( dimMap.size() != 4)        throw NcException("Error in test 7.10",__FILE__,__LINE__);

	dimMap = ncFile.getDims(NcGroup::ParentsAndCurrent);
	if( dimMap.size() != 3)        throw NcException("Error in test 7.11",__FILE__,__LINE__);
	iter=dimMap.find("dim1");
	if( iter == dimMap.end())    throw NcException("Error in test 7.12",__FILE__,__LINE__);
	iter=dimMap.find("dim2");
	if( iter == dimMap.end())    throw NcException("Error in test 7.13",__FILE__,__LINE__);
	iter=dimMap.find("dim3");
	if( iter == dimMap.end())    throw NcException("Error in test 7.14",__FILE__,__LINE__);

	dimMap = ncFile.getDims(NcGroup::All);
	if( dimMap.size() != 7)        throw NcException("Error in test 7.15",__FILE__,__LINE__);
	iter=dimMap.find("dim1");
	if( iter == dimMap.end())    throw NcException("Error in test 7.16",__FILE__,__LINE__);
	iter=dimMap.find("dim2");
	if( iter == dimMap.end())    throw NcException("Error in test 7.17",__FILE__,__LINE__);
	iter=dimMap.find("dim3");
	if( iter == dimMap.end())    throw NcException("Error in test 7.18",__FILE__,__LINE__);
	iter=dimMap.find("dim4");
	if( iter == dimMap.end())    throw NcException("Error in test 7.19",__FILE__,__LINE__);
	iter=dimMap.find("dim5");
	if( iter == dimMap.end())    throw NcException("Error in test 7.20",__FILE__,__LINE__);
	iter=dimMap.find("dim6");
	if( iter == dimMap.end())    throw NcException("Error in test 7.21",__FILE__,__LINE__);
	iter=dimMap.find("dim7");
	if( iter == dimMap.end())    throw NcException("Error in test 7.22",__FILE__,__LINE__);

      }
      cout <<"    -----------   passed\n";



      cout <<left<<setw(55)<<"Testing NcGroup::getDims(\"name\",[netCDF::Location])";
      {

	set<NcDim> dimSet;
	set<NcDim>::iterator iter;

	// operations on ncFile:dim2

	dimSet = ncFile.getDims("dim2");
	if( dimSet.size() != 1)       throw NcException("Error in test 8.1",__FILE__,__LINE__);
	iter=dimSet.find(dim2);
	if( iter == dimSet.end())     throw NcException("Error in test 8.2",__FILE__,__LINE__);
	if( iter->getName() != "dim2")throw NcException("Error in test 8.3",__FILE__,__LINE__);

	dimSet = ncFile.getDims("dim2",NcGroup::Current);
	if( dimSet.count(dim2) != 1) throw NcException("Error in test 8.4",__FILE__,__LINE__);

	dimSet = ncFile.getDims("dim2",NcGroup::Parents);
	if( dimSet.count(dim2) != 0) throw NcException("Error in test 8.5",__FILE__,__LINE__);

	dimSet = ncFile.getDims("dim2",NcGroup::Children);
	if( dimSet.count(dim2) != 0) throw NcException("Error in test 8.6",__FILE__,__LINE__);

	dimSet = ncFile.getDims("dim2",NcGroup::ParentsAndCurrent);
	if( dimSet.count(dim2) != 1) throw NcException("Error in test 8.7",__FILE__,__LINE__);

	dimSet = ncFile.getDims("dim2",NcGroup::ChildrenAndCurrent);
	if( dimSet.count(dim2) != 1) throw NcException("Error in test 8.8",__FILE__,__LINE__);

	dimSet = ncFile.getDims("dim2",NcGroup::All);
	if( dimSet.count(dim2) != 1) throw NcException("Error in test 8.9",__FILE__,__LINE__);


	// operations on ncFile:dim6

	dimSet = ncFile.getDims("dim6");
	if( dimSet.size() != 0)       throw NcException("Error in test 8.10",__FILE__,__LINE__);

	dimSet = ncFile.getDims("dim6",NcGroup::Current);
	if( dimSet.count(dim6) != 0) throw NcException("Error in test 8.11",__FILE__,__LINE__);

	dimSet = ncFile.getDims("dim6",NcGroup::Parents);
	if( dimSet.count(dim6) != 0) throw NcException("Error in test 8.12",__FILE__,__LINE__);

	dimSet = ncFile.getDims("dim6",NcGroup::Children);
	if( dimSet.count(dim6) != 1) throw NcException("Error in test 8.13",__FILE__,__LINE__);

	dimSet = ncFile.getDims("dim6",NcGroup::ParentsAndCurrent);
	if( dimSet.count(dim6) != 0) throw NcException("Error in test 8.14",__FILE__,__LINE__);

	dimSet = ncFile.getDims("dim6",NcGroup::ChildrenAndCurrent);
	if( dimSet.count(dim6) != 1) throw NcException("Error in test 8.15",__FILE__,__LINE__);

	dimSet = ncFile.getDims("dim6",NcGroup::All);
	if( dimSet.count(dim6) != 1) throw NcException("Error in test 8.16",__FILE__,__LINE__);


	// operations on groupB:dim1

	dimSet = groupB.getDims("dim1");
	if( dimSet.size() != 0)       throw NcException("Error in test 8.17",__FILE__,__LINE__);

	dimSet = groupB.getDims("dim1",NcGroup::Current);
	if( dimSet.count(dim1) != 0) throw NcException("Error in test 8.18",__FILE__,__LINE__);

	dimSet = groupB.getDims("dim1",NcGroup::Parents);
	if( dimSet.count(dim1) != 1) throw NcException("Error in test 8.19",__FILE__,__LINE__);

	dimSet = groupB.getDims("dim1",NcGroup::Children);
	if( dimSet.count(dim1) != 0) throw NcException("Error in test 8.20",__FILE__,__LINE__);

	dimSet = groupB.getDims("dim1",NcGroup::ParentsAndCurrent);
	if( dimSet.count(dim1) != 1) throw NcException("Error in test 8.21",__FILE__,__LINE__);

	dimSet = groupB.getDims("dim1",NcGroup::ChildrenAndCurrent);
	if( dimSet.count(dim1) != 0) throw NcException("Error in test 8.22",__FILE__,__LINE__);

	dimSet = groupB.getDims("dim1",NcGroup::All);
	if( dimSet.count(dim1) != 1) throw NcException("Error in test 8.23",__FILE__,__LINE__);


	// operations on groupA:dim1

	dimSet = groupA.getDims("dim1");
	if( dimSet.size() != 0)       throw NcException("Error in test 8.24",__FILE__,__LINE__);

	dimSet = groupA.getDims("dim1",NcGroup::Current);
	if( dimSet.count(dim1) != 0) throw NcException("Error in test 8.25",__FILE__,__LINE__);

	dimSet = groupA.getDims("dim1",NcGroup::Parents);
	if( dimSet.count(dim1) != 1) throw NcException("Error in test 8.26",__FILE__,__LINE__);

	dimSet = groupA.getDims("dim1",NcGroup::Children);
	if( dimSet.count(dim1) != 0) throw NcException("Error in test 8.27",__FILE__,__LINE__);

	dimSet = groupA.getDims("dim1",NcGroup::ParentsAndCurrent);
	if( dimSet.count(dim1) != 1) throw NcException("Error in test 8.28",__FILE__,__LINE__);

	dimSet = groupA.getDims("dim1",NcGroup::ChildrenAndCurrent);
	if( dimSet.count(dim1) != 0) throw NcException("Error in test 8.29",__FILE__,__LINE__);

	dimSet = groupA.getDims("dim1",NcGroup::All);
	if( dimSet.count(dim1) != 1) throw NcException("Error in test 8.30",__FILE__,__LINE__);

      }
      cout <<"    -----------   passed\n";





      cout <<left<<setw(55)<<"Testing NcGroup::getDim(\"name\",[netCDF::Location])";
      {
        if( ncFile.getDim("dim1",NcGroup::All).getName() !="dim1") throw NcException("Error in test 9.1",__FILE__,__LINE__);
        if( ncFile.getDim("dim2",NcGroup::All).getName() !="dim2") throw NcException("Error in test 9.2",__FILE__,__LINE__);
        if( ncFile.getDim("dim3",NcGroup::All).getName() !="dim3") throw NcException("Error in test 9.3",__FILE__,__LINE__);
        if( ncFile.getDim("dim4",NcGroup::All).getName() !="dim4") throw NcException("Error in test 9.4",__FILE__,__LINE__);
        if( ncFile.getDim("dim5",NcGroup::All).getName() !="dim5") throw NcException("Error in test 9.5",__FILE__,__LINE__);
        if( ncFile.getDim("dim6",NcGroup::All).getName() !="dim6") throw NcException("Error in test 9.6",__FILE__,__LINE__);
        if( ncFile.getDim("dim7",NcGroup::All).getName() !="dim7") throw NcException("Error in test 9.7",__FILE__,__LINE__);
        if( groupB.getDim("dim1",NcGroup::All).getName() !="dim1") throw NcException("Error in test 9.8",__FILE__,__LINE__);
        if( groupB.getDim("dim2",NcGroup::All).getName() !="dim2") throw NcException("Error in test 9.9",__FILE__,__LINE__);
        if( groupB.getDim("dim3",NcGroup::All).getName() !="dim3") throw NcException("Error in test 9.10",__FILE__,__LINE__);
        if( groupB.getDim("dim4",NcGroup::All).getName() !="dim4") throw NcException("Error in test 9.11",__FILE__,__LINE__);
        if( groupB.getDim("dim5",NcGroup::All).getName() !="dim5") throw NcException("Error in test 9.12",__FILE__,__LINE__);
        if( groupB.getDim("dim6",NcGroup::All).getName() !="dim6") throw NcException("Error in test 9.13",__FILE__,__LINE__);
        if( groupB.getDim("dim7",NcGroup::All).getName() !="dim7") throw NcException("Error in test 9.14",__FILE__,__LINE__);
        if( !ncFile.getDim("dim7").isNull())                            throw NcException("Error in test 9.15",__FILE__,__LINE__);
        if( !ncFile.getDim("dim7",NcGroup::Current).isNull())           throw NcException("Error in test 9.16",__FILE__,__LINE__);
        if( !ncFile.getDim("dim7",NcGroup::Parents).isNull())           throw NcException("Error in test 9.17",__FILE__,__LINE__);
        if(  ncFile.getDim("dim7",NcGroup::Children).isNull())          throw NcException("Error in test 9.18",__FILE__,__LINE__);
        if( !ncFile.getDim("dim7",NcGroup::ParentsAndCurrent).isNull()) throw NcException("Error in test 9.19",__FILE__,__LINE__);
        if(  ncFile.getDim("dim7",NcGroup::ChildrenAndCurrent).isNull())throw NcException("Error in test 9.20",__FILE__,__LINE__);

        if( !groupA.getDim("dim7").isNull())                            throw NcException("Error in test 9.21",__FILE__,__LINE__);
        if( !groupA.getDim("dim7",NcGroup::Current).isNull())           throw NcException("Error in test 9.22",__FILE__,__LINE__);
        if( !groupA.getDim("dim7",NcGroup::Parents).isNull())           throw NcException("Error in test 9.23",__FILE__,__LINE__);
        if(  groupA.getDim("dim7",NcGroup::Children).isNull())          throw NcException("Error in test 9.24",__FILE__,__LINE__);
        if( !groupA.getDim("dim7",NcGroup::ParentsAndCurrent).isNull()) throw NcException("Error in test 9.25",__FILE__,__LINE__);
        if(  groupA.getDim("dim7",NcGroup::ChildrenAndCurrent).isNull())throw NcException("Error in test 9.26",__FILE__,__LINE__);
        if(  groupA.getDim("dim7",NcGroup::All).isNull())               throw NcException("Error in test 9.27",__FILE__,__LINE__);

        if(  groupB.getDim("dim7").isNull())                            throw NcException("Error in test 9.28",__FILE__,__LINE__);
        if(  groupB.getDim("dim7",NcGroup::Current).isNull())           throw NcException("Error in test 9.29",__FILE__,__LINE__);
        if( !groupB.getDim("dim7",NcGroup::Parents).isNull())           throw NcException("Error in test 9.30",__FILE__,__LINE__);
        if( !groupB.getDim("dim7",NcGroup::Children).isNull())          throw NcException("Error in test 9.31",__FILE__,__LINE__);
        if(  groupB.getDim("dim7",NcGroup::ParentsAndCurrent).isNull()) throw NcException("Error in test 9.32",__FILE__,__LINE__);
        if(  groupB.getDim("dim7",NcGroup::ChildrenAndCurrent).isNull())throw NcException("Error in test 9.33",__FILE__,__LINE__);
        if(  groupB.getDim("dim7",NcGroup::All).isNull())               throw NcException("Error in test 9.34",__FILE__,__LINE__);
        if( !ncFile.getDim("dimX",NcGroup::All).isNull())               throw NcException("Error in test 9.35",__FILE__,__LINE__);
      }

      cout <<"    -----------   passed\n";

      cout <<left<<setw(55)<<"Testing NcGroup::getCoordVars([netCDF::Location])";
      {
        if (ncFile.getCoordVars(NcGroup::Current).count("dim1") != 1) throw NcException("Error in test 10.1", __FILE__, __LINE__);
        if (ncFile.getCoordVars(NcGroup::Current).count("dim4") != 0) throw NcException("Error in test 10.2", __FILE__, __LINE__);
        if (ncFile.getCoordVars(NcGroup::Children).count("dim1") != 0) throw NcException("Error in test 10.3", __FILE__, __LINE__);
        if (ncFile.getCoordVars(NcGroup::Children).count("dim4") != 1) throw NcException("Error in test 10.4", __FILE__, __LINE__);
        if (ncFile.getCoordVars(NcGroup::ChildrenAndCurrent).count("dim1") != 1) throw NcException("Error in test 10.5", __FILE__, __LINE__);
        if (ncFile.getCoordVars(NcGroup::ChildrenAndCurrent).count("dim4") != 1) throw NcException("Error in test 10.6", __FILE__, __LINE__);
        if (ncFile.getCoordVars(NcGroup::Parents).count("dim1") != 0) throw NcException("Error in test 10.7", __FILE__, __LINE__);
        if (ncFile.getCoordVars(NcGroup::Parents).count("dim4") != 0) throw NcException("Error in test 10.8", __FILE__, __LINE__);
        if (ncFile.getCoordVars(NcGroup::ParentsAndCurrent).count("dim1") != 1) throw NcException("Error in test 10.9", __FILE__, __LINE__);
        if (ncFile.getCoordVars(NcGroup::ParentsAndCurrent).count("dim4") != 0) throw NcException("Error in test 10.10", __FILE__, __LINE__);
        if (ncFile.getCoordVars(NcGroup::All).count("dim1") != 1) throw NcException("Error in test 10.11", __FILE__, __LINE__);
        if (ncFile.getCoordVars(NcGroup::All).count("dim4") != 1) throw NcException("Error in test 10.12", __FILE__, __LINE__);

        if (groupA.getCoordVars(NcGroup::Current).count("dim1") != 0) throw NcException("Error in test 10.13", __FILE__, __LINE__);
        if (groupA.getCoordVars(NcGroup::Current).count("dim4") != 0) throw NcException("Error in test 10.14", __FILE__, __LINE__);
        if (groupA.getCoordVars(NcGroup::Children).count("dim1") != 0) throw NcException("Error in test 10.15", __FILE__, __LINE__);
        if (groupA.getCoordVars(NcGroup::Children).count("dim4") != 1) throw NcException("Error in test 10.16", __FILE__, __LINE__);
        if (groupA.getCoordVars(NcGroup::ChildrenAndCurrent).count("dim1") != 0) throw NcException("Error in test 10.17", __FILE__, __LINE__);
        if (groupA.getCoordVars(NcGroup::ChildrenAndCurrent).count("dim4") != 1) throw NcException("Error in test 10.18", __FILE__, __LINE__);
        if (groupA.getCoordVars(NcGroup::Parents).count("dim1") != 1) throw NcException("Error in test 10.19", __FILE__, __LINE__);
        if (groupA.getCoordVars(NcGroup::Parents).count("dim4") != 0) throw NcException("Error in test 10.20", __FILE__, __LINE__);
        if (groupA.getCoordVars(NcGroup::ParentsAndCurrent).count("dim1") != 1) throw NcException("Error in test 10.21", __FILE__, __LINE__);
        if (groupA.getCoordVars(NcGroup::ParentsAndCurrent).count("dim4") != 0) throw NcException("Error in test 10.22", __FILE__, __LINE__);
        if (groupA.getCoordVars(NcGroup::All).count("dim1") != 1) throw NcException("Error in test 10.23", __FILE__, __LINE__);
        if (groupA.getCoordVars(NcGroup::All).count("dim4") != 1) throw NcException("Error in test 10.24", __FILE__, __LINE__);

        if (groupB.getCoordVars(NcGroup::Current).count("dim1") != 0) throw NcException("Error in test 10.25", __FILE__, __LINE__);
        if (groupB.getCoordVars(NcGroup::Current).count("dim4") != 1) throw NcException("Error in test 10.26", __FILE__, __LINE__);
        if (groupB.getCoordVars(NcGroup::Children).count("dim1") != 0) throw NcException("Error in test 10.27", __FILE__, __LINE__);
        if (groupB.getCoordVars(NcGroup::Children).count("dim4") != 0) throw NcException("Error in test 10.28", __FILE__, __LINE__);
        if (groupB.getCoordVars(NcGroup::ChildrenAndCurrent).count("dim1") != 0) throw NcException("Error in test 10.29", __FILE__, __LINE__);
        if (groupB.getCoordVars(NcGroup::ChildrenAndCurrent).count("dim4") != 1) throw NcException("Error in test 10.30", __FILE__, __LINE__);
        if (groupB.getCoordVars(NcGroup::Parents).count("dim1") != 1) throw NcException("Error in test 10.31", __FILE__, __LINE__);
        if (groupB.getCoordVars(NcGroup::Parents).count("dim4") != 0) throw NcException("Error in test 10.32", __FILE__, __LINE__);
        if (groupB.getCoordVars(NcGroup::ParentsAndCurrent).count("dim1") != 1) throw NcException("Error in test 10.33", __FILE__, __LINE__);
        if (groupB.getCoordVars(NcGroup::ParentsAndCurrent).count("dim4") != 1) throw NcException("Error in test 10.34", __FILE__, __LINE__);
        if (groupB.getCoordVars(NcGroup::All).count("dim1") != 1) throw NcException("Error in test 10.35", __FILE__, __LINE__);
        if (groupB.getCoordVars(NcGroup::All).count("dim4") != 1) throw NcException("Error in test 10.36", __FILE__, __LINE__);
      }

      cout <<"    -----------   passed\n";

      cout <<left<<setw(55)<<"Testing NcGroup::getCoordVars([netCDF::Location])";
      {
        NcDim dim;
        NcVar var;

        ncFile.getCoordVar("dim1", dim, var, NcGroup::Current);
        if (dim.getName() != "dim1" || var.getName() != "dim1") throw NcException("Error in test 11.1", __FILE__, __LINE__);
        ncFile.getCoordVar("dim1", dim, var, NcGroup::Parents);
        if (!dim.isNull() || !var.isNull()) throw NcException("Error in test 11.2", __FILE__, __LINE__);
        ncFile.getCoordVar("dim1", dim, var, NcGroup::ParentsAndCurrent);
        if (dim.getName() != "dim1" || var.getName() != "dim1") throw NcException("Error in test 11.3", __FILE__, __LINE__);
        ncFile.getCoordVar("dim1", dim, var, NcGroup::Children);
        if (!dim.isNull() || !var.isNull()) throw NcException("Error in test 11.4", __FILE__, __LINE__);
        ncFile.getCoordVar("dim1", dim, var, NcGroup::ChildrenAndCurrent);
        if (dim.getName() != "dim1" || var.getName() != "dim1") throw NcException("Error in test 11.5", __FILE__, __LINE__);
        ncFile.getCoordVar("dim1", dim, var, NcGroup::All);
        if (dim.getName() != "dim1" || var.getName() != "dim1") throw NcException("Error in test 11.6", __FILE__, __LINE__);

        ncFile.getCoordVar("dim4", dim, var, NcGroup::Current);
        if (!dim.isNull() || !var.isNull()) throw NcException("Error in test 11.7", __FILE__, __LINE__);
        ncFile.getCoordVar("dim4", dim, var, NcGroup::Parents);
        if (!dim.isNull() || !var.isNull()) throw NcException("Error in test 11.8", __FILE__, __LINE__);
        ncFile.getCoordVar("dim4", dim, var, NcGroup::ParentsAndCurrent);
        if (!dim.isNull() || !var.isNull()) throw NcException("Error in test 11.9", __FILE__, __LINE__);
        ncFile.getCoordVar("dim4", dim, var, NcGroup::Children);
        if (dim.getName() != "dim4" || var.getName() != "dim4") throw NcException("Error in test 11.10", __FILE__, __LINE__);
        ncFile.getCoordVar("dim4", dim, var, NcGroup::ChildrenAndCurrent);
        if (dim.getName() != "dim4" || var.getName() != "dim4") throw NcException("Error in test 11.11", __FILE__, __LINE__);
        ncFile.getCoordVar("dim4", dim, var, NcGroup::All);
        if (dim.getName() != "dim4" || var.getName() != "dim4") throw NcException("Error in test 11.12", __FILE__, __LINE__);

        groupA.getCoordVar("dim1", dim, var, NcGroup::Current);
        if (!dim.isNull() || !var.isNull()) throw NcException("Error in test 11.13", __FILE__, __LINE__);
        groupA.getCoordVar("dim1", dim, var, NcGroup::Parents);
        if (dim.getName() != "dim1" || var.getName() != "dim1") throw NcException("Error in test 11.14", __FILE__, __LINE__);
        groupA.getCoordVar("dim1", dim, var, NcGroup::ParentsAndCurrent);
        if (dim.getName() != "dim1" || var.getName() != "dim1") throw NcException("Error in test 11.15", __FILE__, __LINE__);
        groupA.getCoordVar("dim1", dim, var, NcGroup::Children);
        if (!dim.isNull() || !var.isNull()) throw NcException("Error in test 11.16", __FILE__, __LINE__);
        groupA.getCoordVar("dim1", dim, var, NcGroup::ChildrenAndCurrent);
        if (!dim.isNull() || !var.isNull()) throw NcException("Error in test 11.17", __FILE__, __LINE__);
        groupA.getCoordVar("dim1", dim, var, NcGroup::All);
        if (dim.getName() != "dim1" || var.getName() != "dim1") throw NcException("Error in test 11.18", __FILE__, __LINE__);

        groupA.getCoordVar("dim4", dim, var, NcGroup::Current);
        if (!dim.isNull() || !var.isNull()) throw NcException("Error in test 11.19", __FILE__, __LINE__);
        groupA.getCoordVar("dim4", dim, var, NcGroup::Parents);
        if (!dim.isNull() || !var.isNull()) throw NcException("Error in test 11.20", __FILE__, __LINE__);
        groupA.getCoordVar("dim4", dim, var, NcGroup::ParentsAndCurrent);
        if (!dim.isNull() || !var.isNull()) throw NcException("Error in test 11.21", __FILE__, __LINE__);
        groupA.getCoordVar("dim4", dim, var, NcGroup::Children);
        if (dim.getName() != "dim4" || var.getName() != "dim4") throw NcException("Error in test 11.22", __FILE__, __LINE__);
        groupA.getCoordVar("dim4", dim, var, NcGroup::ChildrenAndCurrent);
        if (dim.getName() != "dim4" || var.getName() != "dim4") throw NcException("Error in test 11.23", __FILE__, __LINE__);
        groupA.getCoordVar("dim4", dim, var, NcGroup::All);
        if (dim.getName() != "dim4" || var.getName() != "dim4") throw NcException("Error in test 11.24", __FILE__, __LINE__);

        groupB.getCoordVar("dim1", dim, var, NcGroup::Current);
        if (!dim.isNull() || !var.isNull()) throw NcException("Error in test 11.25", __FILE__, __LINE__);
        groupB.getCoordVar("dim1", dim, var, NcGroup::Parents);
        if (dim.getName() != "dim1" || var.getName() != "dim1") throw NcException("Error in test 11.26", __FILE__, __LINE__);
        groupB.getCoordVar("dim1", dim, var, NcGroup::ParentsAndCurrent);
        if (dim.getName() != "dim1" || var.getName() != "dim1") throw NcException("Error in test 11.27", __FILE__, __LINE__);
        groupB.getCoordVar("dim1", dim, var, NcGroup::Children);
        if (!dim.isNull() || !var.isNull()) throw NcException("Error in test 11.28", __FILE__, __LINE__);
        groupB.getCoordVar("dim1", dim, var, NcGroup::ChildrenAndCurrent);
        if (!dim.isNull() || !var.isNull()) throw NcException("Error in test 11.29", __FILE__, __LINE__);
        groupB.getCoordVar("dim1", dim, var, NcGroup::All);
        if (dim.getName() != "dim1" || var.getName() != "dim1") throw NcException("Error in test 11.30", __FILE__, __LINE__);

        groupB.getCoordVar("dim4", dim, var, NcGroup::Current);
        if (dim.getName() != "dim4" || var.getName() != "dim4") throw NcException("Error in test 11.31", __FILE__, __LINE__);
        groupB.getCoordVar("dim4", dim, var, NcGroup::Parents);
        if (!dim.isNull() || !var.isNull()) throw NcException("Error in test 11.32", __FILE__, __LINE__);
        groupB.getCoordVar("dim4", dim, var, NcGroup::ParentsAndCurrent);
        if (dim.getName() != "dim4" || var.getName() != "dim4") throw NcException("Error in test 11.33", __FILE__, __LINE__);
        groupB.getCoordVar("dim4", dim, var, NcGroup::Children);
        if (!dim.isNull() || !var.isNull()) throw NcException("Error in test 11.34", __FILE__, __LINE__);
        groupB.getCoordVar("dim4", dim, var, NcGroup::ChildrenAndCurrent);
        if (dim.getName() != "dim4" || var.getName() != "dim4") throw NcException("Error in test 11.35", __FILE__, __LINE__);
        groupB.getCoordVar("dim4", dim, var, NcGroup::All);
        if (dim.getName() != "dim4" || var.getName() != "dim4") throw NcException("Error in test 11.36", __FILE__, __LINE__);
      }
      cout <<"    -----------   passed\n";

    }
  catch (NcException& e)
    {

      cout <<"\n";
      cout << e.what() << std::endl;
      return 1;

    }
}
