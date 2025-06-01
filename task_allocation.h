#ifndef TASK_ALLOCATION_H
#define TASK_ALLOCATION_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QSet>


// 数据结构定义
struct RWXX {
    QString ID;
    QString DDXH;       // 货物属性1
    QString ZDBLX;      // 货物属性2
    QString DDPC;       // 货物属性3
    QString TFZZPZBZ;   // 货物属性4
    QString ZDZZPZBZ;   // 货物属性5
    QString DWBH;       // 货物在车上的位置编号
    QString MZDBH;      // 参考点编号
    QString ZZQBH;      // 片区编号
    QString MZD_JD;     // 参考点经度
    QString MZD_WD;     // 参考点纬度
    QString MZD_GC;     // 参考点高程
};

struct BLXX {
    QString FSDYBH;     // 车辆编号
    QString FSYBDNM;    // 所属车队（从车辆编号解析）
    QString ZDZDSL;     // 车辆最大载货数量

    struct DD {
        int DWH;        // 车辆载货位置
        QString DDXH;   // 货物属性1
        QString ZDBLX;  // 货物属性2
        QString DDPC;   // 货物属性3
        QString TFZZPZBZ; // 货物属性4
        QString ZDZZPZBZ; // 货物属性5
    };
    QVector<DD> V_ZDXX; // 所载货物信息

    struct FSDYKZDXX {
        QString DDXH;   // 货物属性1
        QString ZDBLX;  // 货物属性2
    };
    QVector<FSDYKZDXX> FSDYKZDXX; // 所载货物信息

    QString FSDY_JD;    // 车辆当前位置经度
    QString FSDY_WD;    // 车辆当前位置纬度
    QString FSDY_GC;    // 车辆当前位置高程




    struct FSDY_TO_FSZD {
        QString FSZDBH; // 卸货点编号
        QString JL;     // 距离
    };
    QVector<FSDY_TO_FSZD> V_FSDY_TO_FSZD; // 车辆与所有可用卸货点之间的距离

    struct FSDY_TO_FSQ {
        QString FSQBH;  // 卸货区编号
        QString JL;     // 距离
    };
    QVector<FSDY_TO_FSQ> FSDY_KYFSQJL;   // 车辆与所有可用卸货区之间的距离
};

struct ZCXX {
    QString ZZQBH;      // 片区编号

    struct FSZD {
        QString FSZDBH; // 卸货点编号
        QString FSZD_JD; // 卸货点经度
        QString FSZD_WD; // 卸货点纬度
        QString FSZD_GC; // 卸货点高程
        int FSZDPX_IDX; // 卸货点排序索引
    };
    QVector<FSZD> V_FSZD; // 卸货点列表

    struct FSQ {
        QString FSQBH;  // 卸货区编号
        QString FSQ_JD; // 卸货区经度
        QString FSQ_WD; // 卸货区纬度
        QString FSQ_GC; // 卸货区高程
        QString FSQ_RL; // 卸货区容量
        int FSQPX_IDX; // 卸货区排序索引
    };
    QVector<FSQ> V_FSQ; // 卸货区列表
};

struct YZPZXX {
    int YXJ; // 取值0,1,  0表示用户指定优先的优先级最高，1表示默认规则的优先级最高

    struct VehiclePrinciple {
        int ZZSLJKNS; // 货物转载数量尽可能少
        int CJZS;    // 成建制使用
        int BMKQZZ;   // 避免跨区作战
        int JZFS;     // 任务集中/分散

        int DYSL;     // 车辆数量最少/最多
        int BTZPPBTDY; // 不同组匹配不同车辆

        struct SpecifiedVehiclePriority {
            int SFZDYX; // 是否指定优先
            int SYSX;   // 使用顺序

            struct Fleet {
                QString fSYBDNM; // 车队编号
                int FSYYXJ;  // 优先级
                struct Vehicle {
                    QString FSDYBDNM; // 车辆编号
                    int FSYYXJ;   // 优先级
                };
                QVector<Vehicle> FSDY; // 车辆列表
            };
            QVector<Fleet> FSY; // 车队列表
        };
        SpecifiedVehiclePriority ZDBLYX;
    };
    VehiclePrinciple BLYYYZ;

    struct BattlefieldPrinciple {
        int BMPMDDJC; // 避免平面弹道交叉
        int YGYYGFSQ; // 一个车队一个卸货区域
        int FSQYX;    // 卸货区/卸货点优先
        int FSZDYX;   // 任务集中/分散
        int SYSX;     // 顺序/反序/就近/预设

        struct DeploymentPreset {
            struct FleetToUnloadArea {
                QString fSYBDNM; // 车队编号
                QString FSQBH;   // 卸货区编号
            };
            QVector<FleetToUnloadArea> FSYBSYX; // 车队-卸货区预设

            struct VehicleToUnloadPoint {
                QString FSDYBDNM; // 车辆编号
                QString FSZDBH;   // 卸货点编号
            };
            QVector<VehicleToUnloadPoint> FSDYBSYX; // 车辆-卸货点预设
        };
        DeploymentPreset BSYXXX; // 部署预想信息

        struct SpecifiedAreaPriority {
            struct UnloadPoint {
                QString FSZDBH;  // 卸货点编号
                int FSZDYXJ; // 优先级
            };
            QVector<UnloadPoint> FSZD; // 卸货点优先级

            struct UnloadArea {
                QString FSQBH;   // 卸货区编号
                int FSQYXJ;  // 优先级
            };
            QVector<UnloadArea> FSQ; // 卸货区优先级
        };
        SpecifiedAreaPriority ZDZCYX; // 指定卸货位置优先
    };
    BattlefieldPrinciple ZCYYYZ; //卸货位置运用原则
};

struct InputData {
    QVector<RWXX> V_RWXX;   // 任务信息 // 任务信息
    QVector<BLXX> V_BLXX; // 车队信息信息
    QVector<ZCXX> V_ZCXX; // 卸货位置信息
    YZPZXX C_YZPZXX; // 原则配置信息
};

struct OutputData {
    QString SFCG; // 是否成功

    struct Allocation {
        QString ID;         // 任务ID
        QString FSDYBDNM;   // 车辆编号
        QString FSWZBH;     // 卸货位置编号
        QString FSWZLX;     // 卸货位置类型  取值0,1   0表示卸货点，1表示卸货区
    };
    QVector<Allocation> FPXL; // 分配序列
    QString CWXX; // 错误信息
};

class TaskAllocationAlgorithm {
public:
    TaskAllocationAlgorithm();
    ~TaskAllocationAlgorithm();


};

#endif // TASK_ALLOCATION_H
