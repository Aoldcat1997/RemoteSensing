//#include "gdal_priv.h"
//
//#include <errno.h>
//
//int main()
//{
//    // �ļ�·��
//    const char* pszFilename = "E:\\gdal\\gdal-master\\data\\gdalicon.png";
//    const char* pszDstFilename = "E:\\gdal\\gdal-master\\data\\gdalicon1.png";
//    // ��������ָ��
//    // ���ݼ�����ָ�룬�������ڴ���֫
//    GDALDatasetUniquePtr poDataset;
//    GDALAllRegister();
//    // ö�����ͣ�����ֻ����ɸ���
//    const GDALAccess eAccess = GA_ReadOnly;
//    // ǰ��ת������ FromHandle Convert a GDALDatasetH to a GDALDataset*
//    poDataset = GDALDatasetUniquePtr(GDALDataset::FromHandle(GDALOpen(pszFilename, eAccess)));
//    if (!poDataset)
//    {
//         // handle error
//    }
//    // ��������ת������
//    double        adfGeoTransform[6];
//    printf("Driver: %s/%s\n",
//        poDataset->GetDriver()->GetDescription(),
//        poDataset->GetDriver()->GetMetadataItem(GDAL_DMD_LONGNAME));
//    printf("Size is %dx%dx%d\n",
//        // ��ȡ��Ԫ��С
//        poDataset->GetRasterXSize(), poDataset->GetRasterYSize(),
//        poDataset->GetRasterCount());
//    if (poDataset->GetProjectionRef() != NULL)
//        printf("Projection is `%s'\n", poDataset->GetProjectionRef());
//    if (poDataset->GetGeoTransform(adfGeoTransform) == CE_None)
//    {
//        printf("Origin = (%.6f,%.6f)\n",
//            adfGeoTransform[0], adfGeoTransform[3]);
//        printf("Pixel Size = (%.6f,%.6f)\n",
//            adfGeoTransform[1], adfGeoTransform[5]);
//    }
//    // ��ȡդ�񲨶�
//    GDALRasterBand* poBand;
//    int             nBlockXSize, nBlockYSize;
//    int             bGotMin, bGotMax;
//    double          adfMinMax[2];
//    // ��ȡ��һ����
//    poBand = poDataset->GetRasterBand(1);
//    poBand->GetBlockSize(&nBlockXSize, &nBlockYSize);
//    printf("Block=%dx%d Type=%s, ColorInterp=%s\n",
//        nBlockXSize, nBlockYSize,
//        GDALGetDataTypeName(poBand->GetRasterDataType()),
//        GDALGetColorInterpretationName(
//            poBand->GetColorInterpretation()));
//    // ��ȡ��Сֵ��
//    adfMinMax[0] = poBand->GetMinimum(&bGotMin);
//    // ��ȡ���ֵ
//    adfMinMax[1] = poBand->GetMaximum(&bGotMax);
//    // �������ֵΪ�գ������ú����������ֵ����Сֵ
//    if (!(bGotMin && bGotMax))
//        GDALComputeRasterMinMax((GDALRasterBandH)poBand, TRUE, adfMinMax);
//    printf("Min=%.3fd, Max=%.3f\n", adfMinMax[0], adfMinMax[1]);
//    if (poBand->GetOverviewCount() > 0)
//        printf("Band has %d overviews.\n", poBand->GetOverviewCount());
//    if (poBand->GetColorTable() != NULL)
//        printf("Band has a color table with %d entries.\n",
//            poBand->GetColorTable()->GetColorEntryCount());
//    // RasterIO ��ȡդ��
//    float* pafScanline;
//    int   nXSize = poBand->GetXSize();
//    pafScanline = (float*)CPLMalloc(sizeof(float) * nXSize);
//    poBand->RasterIO(GF_Read, 0, 0, nXSize, 1,
//        pafScanline, nXSize, 1, GDT_Float32,
//        0, 0);
//    // ����դ���ļ�
//    const char* pszFormat = "GTiff";
//    GDALDriver* poDriver;
//    char** papszMetadata;
//    poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);
//    if (poDriver == NULL)
//        exit(1);
//    papszMetadata = poDriver->GetMetadata();
//    //��ѯ��䣬��ѯ���ؼ��ַ���True else false
//    if (CSLFetchBoolean(papszMetadata, GDAL_DCAP_CREATE, FALSE))
//        printf("Driver %s supports Create() method.\n", pszFormat);
//    if (CSLFetchBoolean(papszMetadata, GDAL_DCAP_CREATECOPY, FALSE))
//        printf("Driver %s supports CreateCopy() method.\n", pszFormat);
//    // ʹ��createcopy�����ļ�
//    GDALDataset* poSrcDS =
//        (GDALDataset*)GDALOpen(pszFilename, GA_ReadOnly);
//    GDALDataset* poDstDS;
//    poDstDS = poDriver->CreateCopy(pszDstFilename, poSrcDS, FALSE,
//        NULL, NULL, NULL);
//    /* Once we're done, close properly the dataset */
//    // �ر�����
//    if (poDstDS != NULL)
//        printf("successfully copy ");
//        GDALClose((GDALDatasetH)poDstDS);
//    GDALClose((GDALDatasetH)poSrcDS);
//    // CreateCopy���� ��������һ����д���ݼ������ұ�����ȷ�رո����ݼ�������ɽ����ݼ�д���ˢ�µ�����
//    // A more complex case might involve passing creation options, 
//    // and using a predefined progress monitor like this:
//    char** papszOptions = NULL;
//    // papszOptions:�б����ڴ洢name �� value
//    papszOptions = CSLSetNameValue(papszOptions, "TILED", "YES");
//    papszOptions = CSLSetNameValue(papszOptions, "COMPRESS", "PACKBITS");
//    poDstDS = poDriver->CreateCopy(pszDstFilename, poSrcDS, FALSE,
//        papszOptions, GDALTermProgress, NULL);
//    /* Once we're done, close properly the dataset */
//    if (poDstDS != NULL)
//        GDALClose((GDALDatasetH)poDstDS);
//    CSLDestroy(papszOptions);
//     //create ,����
//    GDALDataset* poDstDS;
//    char** papszOptions = NULL;
//    poDstDS = poDriver->Create(pszDstFilename, 512, 512, 1, GDT_Byte,
//        papszOptions);
//    // �������ݲ�д��ͶӰ
//    double adfGeoTransform[6] = { 444720, 30, 0, 3751320, 0, -30 };
//    OGRSpatialReference oSRS;
//    char* pszSRS_WKT = NULL;
//    GDALRasterBand* poBand;
//    GByte abyRaster[512 * 512];
//    poDstDS->SetGeoTransform(adfGeoTransform);
//    oSRS.SetUTM(11, TRUE);
//    oSRS.SetWellKnownGeogCS("NAD27");
//    oSRS.exportToWkt(&pszSRS_WKT);
//    poDstDS->SetProjection(pszSRS_WKT);
//    CPLFree(pszSRS_WKT);
//    poBand = poDstDS->GetRasterBand(1);
//    poBand->RasterIO(GF_Write, 0, 0, 512, 512,
//        abyRaster, 512, 512, GDT_Byte, 0, 0);
//    /* Once we're done, close properly the dataset */
//    GDALClose((GDALDatasetH)poDstDS);
//    return 0;
//}