//#include "ogrsf_frmts.h"
////矢量读写头文件
//int main()
//
//{
//    //自动注册所有驱动，根据数据后缀索引驱动
//    GDALAllRegister();
//    //读取数据指针
//    //static_cast：强制类型转换
//    GDALDataset* poDS = static_cast<GDALDataset*>(
//        GDALOpenEx("point.shp", GDAL_OF_VECTOR, NULL, NULL, NULL));
//    //判定数据是否读取成功
//    if (poDS == NULL)
//    {
//        printf("Open failed.\n");
//        exit(1);
//    }
//    // 根据图层名获取图层
//    //GetLayerByName:类成员函数
//    OGRLayer* poLayer = poDS->GetLayerByName("point");
//    //获取图层所有属性字段
//    OGRFeatureDefn* poFDefn = poLayer->GetLayerDefn();
//
//    poLayer->ResetReading();
//    OGRFeature* poFeature;
//    // Fetch the next available feature from this dataset.
//    while ((poFeature = poLayer->GetNextFeature()) != NULL)
//    {
//        // GetFieldCount:获取当前字段的数量
//        for (int iField = 0; iField < poFDefn->GetFieldCount(); iField++)
//        {
//            /// 测试一个字段是都被分配了值
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
//        //获取特征几何信息:点、线、面
//        //The lifetime of the returned geometry is bound to the one of its belonging feature.
//        OGRGeometry* poGeometry = poFeature->GetGeometryRef();
//        //判定是否存在点
//        //wkbPoint枚举类型
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
//        //释放内存，赋值及申请了新的内存，自己要进行释放
//        OGRFeature::DestroyFeature(poFeature);
//    }
//
//    GDALClose(poDS);
//}