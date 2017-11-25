//FREE TO CUSTOMIZE

/*
 * =========================================================================================
 * Name        : processData.cpp
 * Description : student code for Assignment 1 - Data structures and Algorithms - Fall 2017
 * =========================================================================================
 */
#include "eventLib.h"
#include "dbLib.h"
using namespace std;
void releaseBusGlobalData(){};
void releaseNinjaGlobalData(){};

struct ninja_statistic
{
	char id[ID_MAX_LENGTH];
	double tempLongitude, tempLatitude;
	double distance;
	time_t timestamp;
	int all_time;
	int time_move;
	int time_stop;
};

template <class T>
void SortMaxtoMin(L1List<T> list)
{
	for (int i = 0; i < list.getSize(); i++)
	{
		for (int j = list.getSize() - 1; j > i; j--)
		{
			L1Item<T> *ptmp = list._head;
			//move to list[j-1]
			for (int k = 0; k < j - 1; k++)
			{
				ptmp = ptmp->next;
			}
			//move to list[j]
			L1Item<T> *ptmp2 = ptmp->next;
			if (ptmp2->data > ptmp->data)
			{
				T temp = ptmp2->data;
				ptmp2->data = ptmp->data;
				ptmp->data = temp;
			}
		}
	}
}

void ZerothRequest(string str, L1List<NinjaInfo_t> nList, void *pGdata)
{
	L1List<ninjaEvent_t> eList;
	loadEvents("events.txt", eList);
	cout << str << ": ";
	//Danh sách các mã yêu cầu trong tập tin events.txt
	L1Item<ninjaEvent> *pEventHead = eList._head;
	while (pEventHead)
	{
		cout << pEventHead->data.code << " ";
		pEventHead = pEventHead->next;
	}
	cout << endl;
}
void FirstRequest(string str, L1List<NinjaInfo_t> nList)
{
	//Số hiệu ninja được lưu trữ đầu tiên.
	cout << str << ": ";
	cout << nList._head->data.id;
	cout << endl;
}
void SecondRequest(string str, L1List<NinjaInfo_t> nList)
{
	//Số hiệu ninja được lưu trữ cuối cùng.
	cout << str << ": ";
	cout << nList._tail->data.id;
	cout << endl;
}
void ThirdRequest(string str, L1List<NinjaInfo_t> nList)
{
	//Số lượng ninja đang tham gia cuộc thi.
	cout << str << ": ";
	int count;
	if (nList.isEmpty())
	{
		cout << "There's 0 ninja" << endl;
		return;
	}
	count = 1;
	L1Item<NinjaInfo> *pHead = nList._head;
	for (int i = 0; i < nList.getSize() - 1; i++)
	{
		if (strcmp(pHead->data.id, pHead->next->data.id) != 0)
			count++;
		pHead = pHead->next;
	}
	cout << count << endl;
}
void FourthRequest(string str, L1List<NinjaInfo_t> nList)
{
	//cout << "4: ";
	cout << str << ": ";
	if (nList.isEmpty())
	{
		cout << "Not found ninja's database" << endl;
		return;
	}
	//Số hiệu lớn nhất của ninja tham gia cuộc thi.
	L1Item<NinjaInfo_t> *pHead = nList._head;
	char max[ID_MAX_LENGTH];
	strcpy(max, pHead->data.id);
	for (int i = 0; i < nList.getSize(); i++)
	{
		if (strcmp(max, pHead->data.id) < 0)
			strcpy(max, pHead->data.id);
		pHead = pHead->next;
	}
	cout << max << endl;
}
void FifthRequest(string str, L1List<NinjaInfo_t> nList)
{
	//5ABCD: Thời điểm lưu trữ khi ninja có số hiệu ABCD bắt đầu chuyển động lần đầu tiên trong ngày.
	cout << str << ": ";
	if (nList.isEmpty())
	{
		cout << "Not found ninja's database" << endl;
		return;
	}
	stringstream ss;
	for (int i = 1; i < str.length(); i++)
	{
		ss << str[i];
	}
	L1Item<NinjaInfo_t> *pHead = nList._head;
	L1Item<NinjaInfo_t> *root = pHead;
	bool found = false;
	for (int i = 0; i < nList.getSize(); i++)
	{
		if (ss.str() == pHead->data.id)
		{
			found = true;
			root = pHead;
			pHead = pHead->next;
			if (distanceEarth(root->data.latitude, root->data.longitude, pHead->data.latitude, pHead->data.longitude) >= 0.005)
			{
				char time[30];
				strPrintTime(time, root->data.timestamp);
				cout << time << endl;
				break;
			}
			while (pHead)
			{
				if (strcmp(pHead->data.id, root->data.id) != 0) //if root-behind and root is not the same ninja
				{
					char time[30];
					strPrintTime(time, root->data.timestamp);
					//cout << ss.str() << " start moving (first time of day) at: ";
					cout << time << endl;
					break;
				}
				if (distanceEarth(root->data.latitude, root->data.longitude, pHead->data.latitude, pHead->data.longitude) >= 0.005) //compare distance the root-behind and root
				{
					char time[30];
					strPrintTime(time, pHead->data.timestamp);
					//cout << ss.str() << " starts moving (first time of day) at: ";
					cout << time << endl;
					break;
				}
				pHead = pHead->next;
			}
			break;
		}
		pHead = pHead->next;
	}
	if (found == false)
		cout << "-1" << endl;
}
void SixthRequest(string str, L1List<NinjaInfo_t> nList)
{
	//Thời điểm lưu trữ khi ninja có số hiệu ABCD bắt đầu dừng lại lần cuối cùng trong ngày.
	cout << str << ": ";
	if (nList.isEmpty())
	{
		cout << "Not found ninja's database" << endl;
		return;
	}
	stringstream ss;
	for (int i = 1; i < str.length(); i++)
	{
		ss << str[i];
	}
	L1Item<NinjaInfo_t> *pHead = nList._head;
	L1Item<NinjaInfo_t> *root = pHead;
	pHead = pHead->next;
	bool found = false;
	while (pHead)
	{
		if (ss.str() == pHead->data.id)
		{
			found = true;
			root = pHead;
			pHead = pHead->next;
			while (pHead)
			{
				if (strcmp(pHead->data.id, root->data.id) != 0)
					break;																											//if root-behind and root is not the same ninja
				if (distanceEarth(root->data.latitude, root->data.longitude, pHead->data.latitude, pHead->data.longitude) >= 0.005) //compare distance the root-behind and root
				{
					if (pHead->next != NULL)
					{
						root = pHead; //Update root
					}
				}
				pHead = pHead->next;
			}
			break;
		}
		pHead = pHead->next;
	}
	if (found)
	{
		char time[30];
		strPrintTime(time, root->data.timestamp);
		cout << time << endl;
	}
	else
		cout << "-1" << endl;
}
void SeventhRequest(string str, L1List<NinjaInfo_t> nList)
{
	//Tổng số lần ninja có số hiệu ABCD dừng lại trong ngày.
	cout << str << ": ";
	if (nList.isEmpty())
	{
		cout << "Not found ninja's database" << endl;
		return;
	}
	stringstream ss;
	for (int i = 1; i < str.length(); i++)
	{
		ss << str[i];
	}
	L1Item<NinjaInfo_t> *pHead = nList._head;
	L1Item<NinjaInfo_t> *root = pHead;

	int count = 0;
	bool found = false;

	while (pHead)
	{
		if (ss.str() == pHead->data.id)
		{
			found = true;
			root = pHead;
			pHead = pHead->next;
			if (root->next)
			{
				if (distanceEarth(root->next->data.latitude, root->next->data.longitude, root->data.latitude, root->data.longitude) < 0.005)
				{
					count++;
				}
			}
			while (pHead && strcmp(pHead->data.id, root->data.id) == 0)
			{
				if (distanceEarth(root->data.latitude, root->data.longitude, pHead->data.latitude, pHead->data.longitude) >= 0.005)
				{
					root = pHead;
					if (root->next)
					{
						if (distanceEarth(root->next->data.latitude, root->next->data.longitude, root->data.latitude, root->data.longitude) < 0.005)
						{
							count++;
						}
					}
				}
				pHead = pHead->next;
			}
			break;
		}
		pHead = pHead->next;
	}
	if (found)
	{
		cout << count << endl;
	}
	else
		cout << "-1" << endl;
}
void EighthRequest(string str, L1List<NinjaInfo_t> nList)
{
	//Tổng quãng đường di chuyển trong ngày của ninja có số hiệu ABCD
	cout << str << ": ";
	if (nList.isEmpty())
	{
		cout << "Not found ninja's database" << endl;
		return;
	}
	stringstream ss;
	for (int i = 1; i < str.length(); i++)
	{
		ss << str[i];
	}
	L1Item<NinjaInfo_t> *pHead = nList._head;
	L1Item<NinjaInfo_t> *root = pHead;
	bool found = false;
	double distance = 0;
	while (pHead)
	{
		if (ss.str() == pHead->data.id)
		{
			found = true;
			root = pHead;
			pHead = pHead->next;
			while (pHead && strcmp(pHead->data.id, root->data.id) == 0)
			{

				distance += distanceEarth(root->data.latitude, root->data.longitude, pHead->data.latitude, pHead->data.longitude);
				root = pHead;
				pHead = pHead->next;
			}
			break;
		}
		pHead = pHead->next;
	}
	if (found)
	{
		cout << ss.str() << " has moved (km): ";
		cout << distance << endl;
	}
	else
		cout << "-1" << endl;
}

void NinthRequest(string str, L1List<NinjaInfo_t> nList)
{
	//Số hiệu của ninja có tổng quãng đường di chuyển trong ngày dài nhất.
	cout << str << ": ";
	if (nList.isEmpty())
	{
		cout << "Not found ninja's database" << endl;
		return;
	}
	if (nList.isEmpty())
		return;
	L1Item<NinjaInfo_t> *pHead = nList._head;
	L1Item<NinjaInfo_t> *root = pHead;
	pHead = pHead->next; //move to behind root

	double distance = 0;
	double distanceMax = 0;
	char id_maxDistance[ID_MAX_LENGTH];

	while (pHead)
	{
		if (strcmp(root->data.id, pHead->data.id) == 0)
		{
			double d = distanceEarth(root->data.latitude, root->data.longitude, pHead->data.latitude, pHead->data.longitude);
			distance += d;
			root = pHead;
		}
		else
		{
			if (distance > distanceMax)
			{
				distanceMax = distance;
				strcpy(id_maxDistance, root->data.id);
			}
			root = pHead;
			distance = 0;
		}
		pHead = pHead->next;
	}
	if (distance > distanceMax)
	{
		distanceMax = distance;
		strcpy(id_maxDistance, root->data.id);
	}
	cout << id_maxDistance << endl;
}
void TenthRequest(string str, L1List<NinjaInfo_t> nList)
{
	//Số hiệu của ninja có tổng thời gian di chuyển trong ngày nhiều nhất.
	cout << str << ": ";
	if (nList.isEmpty())
	{
		cout << "Not found ninja's database" << endl;
		return;
	}
	//Build the list of time_stop like 12th-request
	L1Item<NinjaInfo_t> *pHead = nList._head;
	L1List<ninja_statistic> *sList = new L1List<ninja_statistic>();
	ninja_statistic root;
	//set root by pHead
	strcpy(root.id, pHead->data.id);
	root.tempLatitude = pHead->data.latitude;
	root.tempLongitude = pHead->data.longitude;
	root.timestamp = pHead->data.timestamp;
	root.time_stop = 0;
	pHead = pHead->next;
	while (true)
	{
		if (pHead != NULL) //if pHead isnt NULL
		{
			if (strcmp(root.id, pHead->data.id) != 0) //another ninja
			{
				//add old root to linkedlist
				sList->push_back(root);
				//set new root by pHead with new id
				strcpy(root.id, pHead->data.id);
				root.tempLatitude = pHead->data.latitude;
				root.tempLongitude = pHead->data.longitude;
				root.timestamp = pHead->data.timestamp;
				root.time_stop = 0; //reset
			}
			else
			{
				//the same ninja
				double d = distanceEarth(root.tempLatitude, root.tempLongitude, pHead->data.latitude, pHead->data.longitude);
				if (d < 0.005) //if ninja stops moving
				{
					root.time_stop += (int)(pHead->data.timestamp - root.timestamp);
				}
				//set new root by pHead with old id
				root.tempLatitude = pHead->data.latitude;
				root.tempLongitude = pHead->data.longitude;
				root.timestamp = pHead->data.timestamp;
			}
		}
		else //if pHead is NULL
		{
			sList->push_back(root);
			break;
		}
		pHead = pHead->next; //move pHead to next
	}

	//Build list entire time of 1 nj in database
	L1List<ninja_statistic> *sList2 = new L1List<ninja_statistic>();
	ninja_statistic root2;
	pHead = nList._head; //reset pHead
	strcpy(root2.id, pHead->data.id);
	root2.timestamp = pHead->data.timestamp;
	root2.all_time = 0;
	pHead = pHead->next;
	while (true)
	{
		if (pHead)
		{
			if (strcmp(root2.id, pHead->data.id) != 0) //another ninja
			{
				sList2->push_back(root2);
				strcpy(root2.id, pHead->data.id);
				root2.timestamp = pHead->data.timestamp;
				root2.all_time = 0;
			}
			else //the same ninja
			{
				root2.all_time = (int)(pHead->data.timestamp - root2.timestamp);
			}
		}
		else //if pHead is null
		{
			sList2->push_back(root2);
			break;
		}
		pHead = pHead->next;
	}
	//merger sList2 to sList
	L1Item<ninja_statistic> *ptmp = sList->_head;
	L1Item<ninja_statistic> *ptmp2 = sList2->_head;
	while (ptmp && ptmp2)
	{
		if (strcmp(ptmp->data.id, ptmp2->data.id) == 0)
		{
			ptmp->data.time_move = ptmp2->data.all_time - ptmp->data.time_stop;
		}
		ptmp = ptmp->next;
		ptmp2 = ptmp2->next;
	}
	ptmp = sList->_head; //reset ptmp
	ninja_statistic nj_max_timemove;
	strcpy(nj_max_timemove.id, ptmp->data.id);
	nj_max_timemove.time_move = ptmp->data.time_move;
	for (int i = 0; i < sList->getSize(); i++)
	{
		if (nj_max_timemove.time_move < ptmp->data.time_move)
		{
			strcpy(nj_max_timemove.id, ptmp->data.id);
			nj_max_timemove.time_move = ptmp->data.time_move;
		}
		ptmp = ptmp->next;
	}
	cout << nj_max_timemove.id << endl;
}
void EleventhRequest(string str, L1List<NinjaInfo_t> nList)
{
	cout << str << ": ";
	if (nList.isEmpty())
	{
		cout << "Not found ninja's database" << endl;
		return;
	}
	stringstream id;
	for (int i = 2; i < str.length(); i++)
	{
		id << str[i];
	}

	L1Item<NinjaInfo_t> *pHead = nList._head;
	L1Item<NinjaInfo_t> *root = pHead; //set root
	L1List<string> nameList;		   //build list of name
	nameList._head = NULL;
	while (true)
	{
		if (pHead) //pHead isnt NULL
		{
			if (strcmp(root->data.id, pHead->data.id) != 0) //another name
			{
				if (id.str() > root->data.id)
				{
					stringstream ss;
					string target;
					ss << root->data.id;
					ss >> target;
					nameList.push_back(target);
					root = pHead; //update root;
				}
			}
		}
		else //pHead is NULL
		{
			if (id.str() > root->data.id)
			{
				stringstream ss;
				string target;
				ss << root->data.id;
				ss >> target;
				nameList.push_back(target);
				root = pHead; //update root;
			}
			break;
		}
		pHead = pHead->next;
	}
	SortMaxtoMin(nameList);
	bool found = false;
	if (nameList._head)
		found = true;
	if (found)
		cout << nameList._head->data << endl;
	else
		cout << "-1" << endl;
}
void TwelfthRequest(string str, L1List<NinjaInfo_t> nList)
{
	//in ra màn hình số hiệu của ninja có tổng thời gian dừng lại lớn nhất.
	//cout << "12: ";
	cout << str << ": ";
	L1Item<NinjaInfo_t> *pHead = nList._head;
	L1List<ninja_statistic> *sList = new L1List<ninja_statistic>();
	L1Item<NinjaInfo_t> *root;
	//set root by pHead
	root = pHead;
	int time_stop = 0;
	pHead = pHead->next;

	double timestopMax = 0;
	char id_maxTime[ID_MAX_LENGTH];
	while (true)
	{
		if (pHead != NULL) //if pHead isnt NULL
		{
			if (strcmp(root->data.id, pHead->data.id) != 0) //another ninja
			{
				//add old root to linkedlist
				if (timestopMax < time_stop)
				{
					timestopMax = time_stop;
					strcpy(id_maxTime, root->data.id);
				}
				//set new root by pHead with new id
				root = pHead;
				time_stop = 0;
			}
			else
			{
				// //the same ninja

				double d = distanceEarth(root->data.latitude, root->data.longitude, pHead->data.latitude, pHead->data.longitude);
				if (d < 0.005) //if ninja stops moving
				{
					time_stop += (int)(pHead->data.timestamp - root->data.timestamp);
				}
				//set new root by pHead with old id
				root = pHead;

				// L1Item<NinjaInfo_t> *ptmp = root;
				// while(distanceEarth(root->data.latitude, root->data.longitude, pHead->data.latitude, pHead->data.longitude) < 0.005 && strcmp(pHead->data.id, root->data.id) == 0)
				// {
				// 	ptmp = pHead;
				// 	pHead = pHead->next;
				// 	if(!pHead) break;
				// }
				// time_stop += (int)(ptmp->data.timestamp - root->data.timestamp);
				// if (distanceEarth(root->data.latitude, root->data.longitude, pHead->data.latitude, pHead->data.longitude) >= 0.005 && strcmp(pHead->data.id, root->data.id) == 0)
				// 	root = pHead;
				// else if(strcmp(pHead->data.id, root->data.id) == 0) {}
				// else
				// 	pHead = ptmp;
				// if(root->data.timestamp != ptmp->data.timestamp) pHead = ptmp;
			}
		}
		else //if pHead is NULL
		{
			if (timestopMax < time_stop)
			{
				timestopMax = time_stop;
				strcpy(id_maxTime, root->data.id);
			}
			break;
		}
		pHead = pHead->next; //move pHead to next
	}
	cout << id_maxTime /*<< " " << timestopMax*/ << endl;
}

void TwelfthRequest_2(string str, L1List<NinjaInfo_t> nList)
{
	cout << str << ": ";
	if (nList.isEmpty())
	{
		cout << "Not found ninja's database" << endl;
		return;
	}
	//Build the list of time_stop like 12th-request
	L1Item<NinjaInfo_t> *pRun = nList._head;
	L1Item<NinjaInfo_t> *root = nList._head;
	L1Item<NinjaInfo_t> *ptmp = root;
	int time_stop = 0;
	int time_stop_Max = 0;
	char id_time_stop_Max[ID_MAX_LENGTH];
	strcpy(id_time_stop_Max, root->data.id);
	pRun = pRun->next;
	while (pRun)
	{
		if (strcmp(pRun->data.id, root->data.id) == 0)
		{
			double d = distanceEarth(root->data.latitude, root->data.longitude, pRun->data.latitude, pRun->data.longitude);
			if (d < 0.005)
			{
				ptmp = pRun;
			}
			else
			{
				time_stop += (int)(ptmp->data.timestamp - root->data.timestamp);
				root = ptmp = pRun;
			}
		}
		else
		{
			time_stop += (int)(ptmp->data.timestamp - root->data.timestamp);
			if (time_stop > time_stop_Max)
			{
				strcpy(id_time_stop_Max, root->data.id);
				time_stop_Max = time_stop;
			}
			time_stop = 0;
			root = ptmp = pRun;
		}
		pRun = pRun->next;
	}
	cout << id_time_stop_Max << " " << time_stop_Max << endl;
}
void ThirteenthRequest(string str, L1List<NinjaInfo_t> nList)
{
	cout << str << ": ";
}

void FourteenthRequest(string str, L1List<NinjaInfo_t> nList)
{
	cout << str << ": ";
	L1List<string> lac_ninja;
	L1List<NinjaInfo_t> nListUpdate;
	L1Item<NinjaInfo_t> *pRun = nList._head;
	L1Item<NinjaInfo_t> *root = pRun;
	nList.push_back(root->data);
	pRun = pRun->next;
	while (pRun)
	{
		if (strcmp(root->data.id, pRun->data.id) == 0)
		{
			if (distanceEarth(root->data.latitude, root->data.longitude, pRun->data.latitude, pRun->data.longitude) >= 0.005)
			{
				if (strcmp(pRun->next->data.id, root->data.id) == 0)
					nListUpdate.push_back(pRun->data);
				root = pRun;
			}
		}
		else
		{
			//check the old one
			L1Item<NinjaInfo_t> *ptmp = nListUpdate._head;
			ptmp = ptmp->next;
			bool lac = false;
			while (ptmp && lac == false)
			{
				L1Item<NinjaInfo_t> *ptmp2 = nListUpdate._head;
				while (ptmp2->data.timestamp != ptmp->data.timestamp)
				{
					if (distanceEarth(ptmp2->data.latitude, ptmp2->data.longitude, ptmp->data.latitude, ptmp->data.longitude) < 0.005)
					{
						lac = true;
						break;
					}
					ptmp2 = ptmp2->next;
				}
				ptmp = ptmp->next;
			}

			if (lac == true)
			{
				stringstream ss;
				string target;
				ss << root->data.id;
				ss >> target;
				lac_ninja.push_back(target);
			}
			//Update root
			root = pRun;
		}
		pRun = pRun->next;
	}
	L1Item<string> *ptmp = lac_ninja._head;
	if (!ptmp)
	{
		cout << "-1" << endl;
		return;
	}
	while (ptmp)
	{
		cout << ptmp->data << " ";
		ptmp = ptmp->next;
	}
	cout << endl;
}

bool processEvent(ninjaEvent_t &event, L1List<NinjaInfo_t> &nList, void *pGdata)
{
	string choice = event.code;
	if (choice == "0")
		ZerothRequest(choice, nList, pGdata); //ok?
	else if (choice == "1")
		FirstRequest(choice, nList); //ok
	else if (choice == "2")
		SecondRequest(choice, nList); //ok
	else if (choice == "3")
		ThirdRequest(choice, nList); //ok
	else if (choice == "4")
		FourthRequest(choice, nList); //ok
	else if (choice == "9")
		NinthRequest(choice, nList); //ok
	else if (choice == "10")
		TenthRequest(choice, nList);
	else if (choice == "12")
		TwelfthRequest_2(choice, nList);
	else if (choice == "14")
		FourteenthRequest(choice, nList); //ok
	else
	{
		if (choice[0] == '5')
			FifthRequest(choice, nList); //ok
		else if (choice[0] == '6')
			SixthRequest(choice, nList);
		else if (choice[0] == '7')
			SeventhRequest(choice, nList); //ok
		else if (choice[0] == '8')
			EighthRequest(choice, nList); //ok
		else
		{
			stringstream ss;
			ss << choice[0] << choice[1];
			if (ss.str() == "11")
				EleventhRequest(choice, nList); //ok
			else if (ss.str() == "13")
				return true; //auto ok
			else
				return false;
		}
	}
	return true;
}
