//
// Created by Aimo on 2022/6/2.
//

#ifndef ACO_INFORMATION_H
#define ACO_INFORMATION_H

const int City_Num = 11;//������Ŀ
const int Alpha = 1;
const int Beta = 5;
const int Q = 100;//��ʾ����ѭ��һ�����ͷŵ���Ϣ������
const double Theta = 0.2;//��ʾ��Ϣ�ص�˥����
const int Ant_num = 50;//��������
const int item = 1000;//��������
const int max_v = 120;//�������
const double Correction_X[City_Num] = {40, 25, 15, 10, 5, 0, 44, 35, 95, 85, 65};//���еĺ�����
const double Correction_Y[City_Num] = {50, 85, 75, 35, 35, 40, 5, 5, 30, 35, 85};//���е�������
const int need[City_Num] = {0, 20, 20, 20, 10, 20, 20, 20, 30, 30, 40};//����ÿ�����е�������


#endif //ACO_INFORMATION_H
