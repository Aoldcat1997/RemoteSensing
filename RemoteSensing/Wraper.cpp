//#include "gdalwarper.h"
//#include"gdal_priv.h"
//// Ӱ��ͶӰ�任
//int main()
//{
//    // ���ݼ��ṹ��ָ��
//    GDALDatasetH  hSrcDS, hDstDS;
//
//    // Open input and output files.
//    // ע��������
//    GDALAllRegister();
//    // �������������������
//    hSrcDS = GDALOpen("E:\\gdal\\test.tif", GA_ReadOnly);
//    hDstDS = GDALOpen("E:\\gdal\\out.tif", GA_Update);
//
//    // Setup warp options.
//    // ���ñ仯ѡ��ͷź�����GDALDestroyWarpOptions
//    GDALWarpOptions* psWarpOptions = GDALCreateWarpOptions();
//    // ԴӰ��
//    psWarpOptions->hSrcDS = hSrcDS;
//    // Ŀ��Ӱ��
//    psWarpOptions->hDstDS = hDstDS;
//    // ��������
//    psWarpOptions->nBandCount = 1;
//    // the band number for source image to process band number 
//    psWarpOptions->panSrcBands =
//        (int*)CPLMalloc(sizeof(int) * psWarpOptions->nBandCount);
//    psWarpOptions->panSrcBands[0] = 1;
//    // the band number for destination image to process band number 
//    psWarpOptions->panDstBands =
//        (int*)CPLMalloc(sizeof(int) * psWarpOptions->nBandCount);
//    psWarpOptions->panDstBands[0] = 1;
//    // ������̱��溯��
//    psWarpOptions->pfnProgress = GDALTermProgress;
//
//    // Establish reprojection transformer.
//    // ����ͶӰת��������GDALCreateGenImgProjTransformer��img1,cood_ref2,img2,cood_ref2��
//    // �ͷź��� GDALDestroyGenImgProjTransformer
//    psWarpOptions->pTransformerArg =
//        GDALCreateGenImgProjTransformer(hSrcDS,
//            GDALGetProjectionRef(hSrcDS),
//            hDstDS,
//            GDALGetProjectionRef(hDstDS),
//            FALSE, 0.0, 1);
//    psWarpOptions->pfnTransformer = GDALGenImgProjTransform;
//
//    // Initialize and execute the warp operation.
//    GDALWarpOperation oOperation;
//    // ִ�б任����
//    // ������ʼ��
//    oOperation.Initialize(psWarpOptions);
//    // ����ƫ������դ����Ԫ��С
//    printf("x:%d,y%d", GDALGetRasterXSize(hDstDS),
//        GDALGetRasterYSize(hDstDS));
//    printf("sizeof(int) * psWarpOptions->nBandCount) size:%zd:", sizeof(int) * psWarpOptions->nBandCount);
//    printf("��������\n");
//    // This method does a complete warp of the source image to 
//    // the destination image for the indicated region with the current warp options in effect.
//    oOperation.ChunkAndWarpImage(0, 0,
//        GDALGetRasterXSize(hDstDS),
//        GDALGetRasterYSize(hDstDS));
//    // �ͷ�ͶӰ�����ڴ�
//    GDALDestroyGenImgProjTransformer(psWarpOptions->pTransformerArg);
//    GDALDestroyWarpOptions(psWarpOptions);
//    // �ر�����
//    GDALClose(hDstDS);
//    GDALClose(hSrcDS);
//    return 0;
//}