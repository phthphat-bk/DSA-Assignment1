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

// struct ninja_statistic
// {
// 	char id[ID_MAX_LENGTH];
// 	double tempLongitude, tempLatitude;
// 	double distance;
// 	time_t timestamp;
// 	int all_time;
// 	int time_move;
// 	int time_stop;
// };

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
	L1List<ninjaEvent_t> *eList = static_cast<L1List<ninjaEvent_t> *>(pGdata);
	//loadEvents("events.txt", eList);
	cout << str << ": ";
	//Danh sách các mã yêu cầu trong tập tin events.txt
	L1Item<ninjaEvent> *pEventHead = eList->_head;
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
	cout << nList.request2nd;
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
	L1Item<NinjaInfo_t> *pHead = nList._head;
	L1Item<NinjaInfo_t> *pCur = pHead;
	pHead = pHead->next;
	while(pHead)
	{
		if (strcmp(pHead->data.id, pCur->data.id) != 0)
		{
			pCur = pHead;
			count++;
		}
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
bool existStopPoint(L1Item<NinjaInfo_t> *p)
{
	L1Item<NinjaInfo_t> *root = p;
	L1Item<NinjaInfo_t> *pRun = root;
	pRun = pRun->next;
	while (pRun && strcmp(pRun->data.id, root->data.id) == 0)
	{
		if (distanceEarth(root->data.latitude, root->data.longitude, pRun->data.latitude, pRun->data.longitude) >= 0.005)
		{
			root = pRun;
		}
		else
			return true;
		pRun = pRun->next;
	}
	return false;
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
			while (pHead && strcmp(pHead->data.id, root->data.id) == 0)
			{
				if (distanceEarth(root->data.latitude, root->data.longitude, pHead->data.latitude, pHead->data.longitude) >= 0.005) //compare distance the root-behind and root
				{
					if (existStopPoint(pHead))
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
		//cout << ss.str() << " has moved (km): ";
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
struct ninja_stat
{
	char id[ID_MAX_LENGTH];
	time_t timeEntire;
	time_t timeStop;
	time_t timeMove;
};
void TenthRequest(string str, L1List<NinjaInfo_t> nList)
{
	//Số hiệu của ninja có tổng thời gian di chuyển trong ngày nhiều nhất.
	cout << str << ": ";
	if (nList.isEmpty())
	{
		cout << "Not found ninja's database" << endl;
		return;
	}
	//Build list of timeStop
	L1Item<NinjaInfo_t> *pRun = nList._head;
	L1Item<NinjaInfo_t> *root = nList._head;
	L1Item<NinjaInfo_t> *ptmp = root;
	L1List<ninja_stat> sList;
	ninja_stat njSt;
	strcpy(njSt.id, root->data.id);
	njSt.timeStop = 0;
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
				njSt.timeStop += ptmp->data.timestamp - root->data.timestamp;
				root = ptmp = pRun;
			}
		}
		else
		{
			njSt.timeStop += ptmp->data.timestamp - root->data.timestamp;
			sList.push_back(njSt);
			njSt.timeStop = 0;
			strcpy(njSt.id, pRun->data.id);
			root = ptmp = pRun;
		}
		pRun = pRun->next;
	}
	njSt.timeStop += ptmp->data.timestamp - root->data.timestamp;
	sList.push_back(njSt);

	//Build list of timeEntire
	L1List<ninja_stat> sList2;
	L1Item<NinjaInfo_t> *root2 = nList._head;
	L1Item<NinjaInfo_t> *pRun2 = nList._head;
	ninja_stat njSt2;
	strcpy(njSt2.id, root2->data.id);
	njSt2.timeEntire = 0;
	pRun2 = pRun2->next;

	while (pRun2)
	{
		if (strcmp(pRun2->data.id, root2->data.id) == 0)
		{
			njSt2.timeEntire += pRun2->data.timestamp - root2->data.timestamp;
			root2 = pRun2;
		}
		else
		{
			sList2.push_back(njSt2);
			root2 = pRun2;
			strcpy(njSt2.id, root2->data.id);
			njSt2.timeEntire = 0;
		}
		pRun2 = pRun2->next;
	}
	sList2.push_back(njSt2);

	//Merge 2 sList and sList2 to sList
	L1Item<ninja_stat> *pHead = sList._head;
	L1Item<ninja_stat> *pHead2 = sList2._head;
	// L1List<ninja_stat> sList3;
	// ninja_stat njSt3;

	while (pHead && pHead2)
	{
		pHead->data.timeMove = pHead2->data.timeEntire - pHead->data.timeStop;
		pHead = pHead->next;
		pHead2 = pHead2->next;
	}

	pHead = sList._head;
	time_t timeMoveMax = pHead->data.timeMove;
	char id_timeMoveMax[ID_MAX_LENGTH];
	strcpy(id_timeMoveMax, pHead->data.id);
	pHead = pHead->next;
	while (pHead)
	{
		if (pHead->data.timeMove > timeMoveMax)
		{
			strcpy(id_timeMoveMax, pHead->data.id);
			timeMoveMax = pHead->data.timeMove;
		}
		pHead = pHead->next;
	}
	cout << id_timeMoveMax << endl;
}
bool deleteID(L1List<NinjaInfo_t> nList, char *id)
{
	if (nList.isEmpty())
		return true;
	L1Item<NinjaInfo_t> *pCur = nList._head;
	L1Item<NinjaInfo_t> *pPre = nList._head;
	pCur = pCur->next;
	bool isDeleted = false;
	while (strcmp(pPre->data.id, id) == 0)
	{
		nList._head = pCur;
		L1Item<NinjaInfo_t> *ptmp = pPre;
		pPre = pPre->next;
		pCur = pCur->next;
		delete ptmp;
		nList._size--;
		isDeleted = true;
	}
	while (pCur)
	{
		if (strcmp(pCur->data.id, id) == 0)
		{
			L1Item<NinjaInfo_t> *ptmp = pCur;
			pPre->next = pCur->next;
			pCur = pCur->next;
			delete ptmp;
			ptmp = NULL;
			nList._size--;
			isDeleted = true;
		}
		else
		{
			pPre = pCur;
			pCur = pCur->next;
		}
	}
	if(isDeleted) return true;
	return false;
}
void EleventhRequest(string str, L1List<NinjaInfo_t> &nList)
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

	char target[ID_MAX_LENGTH];
	strcpy(target, nameList._head->data.c_str());
	deleteID(nList, target);
}

void TwelfthRequest(string str, L1List<NinjaInfo_t> nList)
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
	time_t time_stop = 0;
	time_t time_stop_Max = 0;
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
				time_stop += ptmp->data.timestamp - root->data.timestamp;
				root = ptmp = pRun;
			}
		}
		else
		{
			time_stop += ptmp->data.timestamp - root->data.timestamp;
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
	time_stop += ptmp->data.timestamp - root->data.timestamp;
	if (time_stop > time_stop_Max)
	{
		strcpy(id_time_stop_Max, root->data.id);
		time_stop_Max = time_stop;
	}
	cout << id_time_stop_Max << endl;
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
	nListUpdate.push_back(root->data);
	pRun = pRun->next;
	while (pRun)
	{
		if (strcmp(root->data.id, pRun->data.id) == 0)
		{
			if (distanceEarth(root->data.latitude, root->data.longitude, pRun->data.latitude, pRun->data.longitude) >= 0.005)
			{
				//if (strcmp(pRun->next->data.id, root->data.id) == 0)
				nListUpdate.push_back(pRun->data);
				root = pRun;
			}
		}
		else
		{
			//check the old one
			//nListUpdate.removeLast();
			L1Item<NinjaInfo_t> *ptmp = nListUpdate._head;
			bool lac = false;
			if (nListUpdate._size > 1)
			{
				ptmp = ptmp->next;
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
			nListUpdate.clean();
			nListUpdate.push_back(root->data);
		}
		pRun = pRun->next;
	}
	//nListUpdate.removeLast();
	L1Item<NinjaInfo_t> *ptmp = nListUpdate._head;
	bool lac = false;
	if (nListUpdate._size > 1)
	{
		ptmp = ptmp->next;
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
	}
	if (lac == true)
	{
		stringstream ss;
		string target;
		ss << root->data.id;
		ss >> target;
		lac_ninja.push_back(target);
	}
	L1Item<string> *ptmp3 = lac_ninja._head;

	if (!ptmp3)
	{
		cout << "-1" << endl;
		return;
	}
	while (ptmp3)
	{
		cout << ptmp3->data << " ";
		ptmp3 = ptmp3->next;
	}
	cout << endl;
}

bool processEvent(ninjaEvent_t &event, L1List<NinjaInfo_t> &nList, void *pGdata)
{
	string choice = event.code;
	if (choice == "0")
		ZerothRequest(choice, nList, pGdata); //ok
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
		TenthRequest(choice, nList); //ok
	else if (choice == "12")
		TwelfthRequest(choice, nList); //ok
	else if (choice == "14")
		FourteenthRequest(choice, nList); //ok
	else
	{
		if (choice[0] == '5')
			FifthRequest(choice, nList); //ok
		else if (choice[0] == '6')
			SixthRequest(choice, nList); //ok
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
				return false; //auto ok
			else
				return false;
		}
	}
	return true;
}
