//#include "ogrsf_frmts.h"
////ʸ����дͷ�ļ�
//int main()
//
//{
//    //�Զ�ע�������������������ݺ�׺��������
//    GDALAllRegister();
//    //��ȡ����ָ��
//    //static_cast��ǿ������ת��
//    GDALDataset* poDS = static_cast<GDALDataset*>(
//        GDALOpenEx("point.shp", GDAL_OF_VECTOR, NULL, NULL, NULL));
//    //�ж������Ƿ��ȡ�ɹ�
//    if (poDS == NULL)
//    {
//        printf("Open failed.\n");
//        exit(1);
//    }
//    // ����ͼ������ȡͼ��
//    //GetLayerByName:���Ա����
//    OGRLayer* poLayer = poDS->GetLayerByName("point");
//    //��ȡͼ�����������ֶ�
//    OGRFeatureDefn* poFDefn = poLayer->GetLayerDefn();
//
//    poLayer->ResetReading();
//    OGRFeature* poFeature;
//    // Fetch the next available feature from this dataset.
//    while ((poFeature = poLayer->GetNextFeature()) != NULL)
//    {
//        // GetFieldCount:��ȡ��ǰ�ֶε�����
//        for (int iField = 0; iField < poFDefn->GetFieldCount(); iField++)
//        {
//            /// ����һ���ֶ��Ƕ���������ֵ
//            if (!poFeature->IsFieldSet(iField))
//            {
//                printf("(unset),");
//                continue;
//            }
//            // Test if a field is null.
//            if (poFeature->IsFieldNull(iField))
//            {
//                printf("(null),");
//                continue;
//            }
//            OGRFieldDefn* poFieldDefn = poFDefn->GetFieldDefn(iField);
//
//            switch (poFieldDefn->GetType())
//            {
//            case OFTInteger:
//                printf("%d,", poFeature->GetFieldAsInteger(iField));
//                break;
//            case OFTInteger64:
//                printf(CPL_FRMT_GIB ",", poFeature->GetFieldAsInteger64(iField));
//                break;
//            case OFTReal:
//                printf("%.3f,", poFeature->GetFieldAsDouble(iField));
//                break;
//            case OFTString:
//                printf("%s,", poFeature->GetFieldAsString(iField));
//                break;
//            default:
//                printf("%s,", poFeature->GetFieldAsString(iField));
//                break;
//            }
//        }
//        //��ȡ����������Ϣ:�㡢�ߡ���
//        //The lifetime of the returned geometry is bound to the one of its belonging feature.
//        OGRGeometry* poGeometry = poFeature->GetGeometryRef();
//        //�ж��Ƿ���ڵ�
//        //wkbPointö������
//        if (poGeometry != NULL
//            && wkbFlatten(poGeometry->getGeometryType()) == wkbPoint)
//        {
//            OGRPoint* poPoint = (OGRPoint*)poGeometry;
//
//            printf("%.3f,%3.f\n", poPoint->getX(), poPoint->getY());
//        }
//        else
//        {
//            printf("no point geometry\n");
//        }
//        //�ͷ��ڴ棬��ֵ���������µ��ڴ棬�Լ�Ҫ�����ͷ�
//        OGRFeature::DestroyFeature(poFeature);
//    }
//
//    GDALClose(poDS);
//}