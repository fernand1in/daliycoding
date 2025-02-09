#include "demo4.h"
#include "ui_demo4.h"
#include <iostream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , nodeNames({
          "东南门", "行政楼", "教学楼",
          "图书馆", "信息中心",  "体育馆",
          "商业街", "熹园食堂", "宿舍楼", "北门"
      })
    , graph({
             {0, 161, 410, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
             {161, 0, INT_MAX, INT_MAX, 87, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
             {410, INT_MAX, 0, 209, INT_MAX, INT_MAX, INT_MAX, 233, INT_MAX, INT_MAX},
             {INT_MAX, INT_MAX, 209, 0, 200, 633, INT_MAX, INT_MAX, 729, INT_MAX}, // 图书馆
             {INT_MAX, 87, INT_MAX, 200, 0, 365, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
             {INT_MAX, INT_MAX, INT_MAX, 633, 365, 0, INT_MAX, INT_MAX, INT_MAX, INT_MAX}, // 体育馆
             {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0, 87, 147, 248},
             {INT_MAX, INT_MAX, 233, INT_MAX, INT_MAX, INT_MAX, 87, 0, INT_MAX, INT_MAX},
             {INT_MAX, INT_MAX, INT_MAX, 729, INT_MAX, INT_MAX, 147, INT_MAX, 0, 314},      // 宿舍楼
             {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 248, INT_MAX, 314, 0}})
    , graph_({
              {0, 161, 410, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
              {161, 0, INT_MAX, INT_MAX, 87, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
              {410, INT_MAX, 0, 209, INT_MAX, INT_MAX, INT_MAX, 233, INT_MAX, INT_MAX},
              {INT_MAX, INT_MAX, 209, 0, 200, 633, INT_MAX, INT_MAX, 729, INT_MAX}, // 图书馆
              {INT_MAX, 87, INT_MAX, 200, 0, 365, INT_MAX, INT_MAX, INT_MAX, INT_MAX},
              {INT_MAX, INT_MAX, INT_MAX, 633, 365, 0, INT_MAX, INT_MAX, INT_MAX, INT_MAX}, // 体育馆
              {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0, 87, 147, 248},
              {INT_MAX, INT_MAX, 233, INT_MAX, INT_MAX, INT_MAX, 87, 0, INT_MAX, INT_MAX},
              {INT_MAX, INT_MAX, INT_MAX, 729, INT_MAX, INT_MAX, 147, INT_MAX, 0, 314},      // 宿舍楼
              {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 248, INT_MAX, 314, 0}})
{
    floydWarshall(graph_);
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::on_pushButton_clicked);
    connect(ui->aButton, &QPushButton::clicked, this, &Widget::on_aButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Widget::on_pushButton2_clicked);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::floydWarshall(std::vector<std::vector<int>> &graph) {
    int n = graph.size();
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (graph[i][k] != INT_MAX && graph[k][j] != INT_MAX && graph[i][k] + graph[k][j] < graph[i][j]) {
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
            }
        }
    }
}

int Widget::getGraphIndex(const QString &nodeName) const {
    return std::find(nodeNames.begin(), nodeNames.end(), nodeName) - nodeNames.begin();
}

std::vector<int> Widget::getGraphIndices(const std::vector<QString> &nodeNames) const {
    std::vector<int> indices;
    for (const QString &name : nodeNames) {
        if (name != "无") {
            indices.push_back(getGraphIndex(name));
        }
        // std::cout<<name.toStdString()<<'\n';
    }
    return indices;
}

void Widget::on_pushButton_clicked()
{
    QString startText = ui->comboBox->currentText();
    QString endText = ui->comboBox_2->currentText();
    int start = getGraphIndex(startText);
    int end = getGraphIndex(endText);

    std::set<int> avoid;
    auto result = dijkstra(graph, start, end, avoid);
    std::vector<int> bestPath = result.first;
    int minDistance = result.second;

    QString pathStr;

    for (int node : bestPath) {
        pathStr += nodeNames[node] + " -> ";
    }
    pathStr.chop(4); // Remove the last " -> "
    ui->textEdit->setText("最佳路径:  " + pathStr + "\n最短距离:  " + QString::number(minDistance));
    //new
    // std::vector<int> hamCycle = hamiltonianCycle(graph, start);
    // if (!hamCycle.empty()) {
    //     QString hamCycleStr;
    //     hamCycleStr += nodeNames[start]; // 添加起点
    //     for (int node : hamCycle) {
    //         hamCycleStr += " -> " + nodeNames[node];
    //     }
    //     hamCycleStr += " -> " + nodeNames[start]; // 回到起点，完成回路
    //     ui->textEdit->append("\n哈密顿回路: " + hamCycleStr);
    // } else {
    //     ui->textEdit->append("\n没有找到哈密顿回路。");
    // }

}
void Widget::on_pushButton2_clicked()
{
    // 新增按钮的代码，展示哈密顿回路
    QString startText = ui->comboBox->currentText(); // 从comboBox中获取起点
    int start = getGraphIndex(startText); // 获取起点索引

    std::vector<int> hamCycle = hamiltonianCycle(graph, start); // 从起点开始寻找哈密顿回路
    if (!hamCycle.empty()) {
        QString hamCycleStr;
        hamCycleStr += nodeNames[hamCycle[0]]; // 添加起点
        for (size_t i = 1; i < hamCycle.size(); ++i) {
            hamCycleStr += " -> " + nodeNames[hamCycle[i]];
        }
        hamCycleStr += " -> " + nodeNames[hamCycle[0]]; // 回到起点，完成回路
        ui->textEdit->setText("哈密顿回路: " + hamCycleStr);
    } else {
        ui->textEdit->setText("没有找到哈密顿回路。");
    }
}

void Widget::on_aButton_clicked()
{
    QString startText = ui->comboBox_3->currentText();
    std::vector<QString> targetsText = {
        ui->comboBox_4->currentText(),
        ui->comboBox_5->currentText(),
        ui->comboBox_6->currentText(),
        ui->comboBox_9->currentText(),
        ui->comboBox_10->currentText(),
        ui->comboBox_11->currentText(),
        ui->comboBox_12->currentText(),
        ui->comboBox_13->currentText(),
        ui->comboBox_14->currentText(),
        ui->comboBox_15->currentText(),
        ui->comboBox_17->currentText()
    };

    int start = getGraphIndex(startText);
    std::vector<int> targets = getGraphIndices(targetsText);

    // for(auto p:targets){
    //     std::cout<<p<<'\n';
    // }
    // std::cout<<"up do";

    // 过滤掉“无”目的地
    // targets.erase(std::remove_if(targets.begin(), targets.end(), [this](int index) {
    //                   return nodeNames[index] == "无";
    //               }), targets.end());

    if (targets.empty()) {
        ui->textBrowser->setText("没有设置有效的目的地，无法计算路径。");
        return;
    }

    auto result = findShortestPath(graph_, start, targets);
    std::vector<int> bestPath = result.first;
    int minDistance = result.second;
    auto result_ = extend(bestPath);
    std::vector<int> bestPath_ = result_.first;

    QString pathStr;
    for (int node : bestPath) {
        pathStr += nodeNames[node] + " -> ";
    }
    pathStr.chop(4); // Remove the last " -> "

    QString pathStr_;
    for (int node : bestPath_) {
        pathStr_ += nodeNames[node] + " -> ";
    }
    pathStr_.chop(4); // Remove the last " -> "
    ui->textBrowser->setText("最佳游览顺序: " + pathStr + "\n最短距离: " + QString::number(minDistance) +
                             "\n最优路径推荐: " + pathStr_ + "\n最短距离: " + QString::number(minDistance));
}
//new
bool Widget::hamiltonianCycleUtil(const std::vector<std::vector<int>> &graph, std::vector<int> &path, int pos, int V) {
    if (pos == V) {
        if (graph[path[pos - 1]][path[0]] != INT_MAX) {
            return true;
        }
        return false;
    }

    for (int v = 0; v < V; v++) {
        bool isSafe = true;

        for (int i = 0; i < pos; i++) {
            if (path[i] == v) {
                isSafe = false;
                break;
            }
        }

        if (isSafe && graph[path[pos - 1]][v] != INT_MAX) {
            path[pos] = v;

            if (hamiltonianCycleUtil(graph, path, pos + 1, V)) {
                return true;
            }

            path[pos] = -1;
        }
    }

    return false;
}

std::vector<int> Widget::hamiltonianCycle(const std::vector<std::vector<int>> &graph, int start) {
    int V = graph.size();
    std::vector<int> path(V, -1);
    path[0] = start;

    if (hamiltonianCycleUtil(graph, path, 1, V)) {
        return path;
    }

    return {};
}
std::pair<std::vector<int>, int> Widget::extend(std::vector<int> poi) {
    std::vector<int> answer;
    int len = 0;
    std::set<int>temp;
    for(int i = 0; i < poi.size() - 1; i++) {
        auto [a, b] = dijkstra(graph, poi[i], poi[i + 1], temp);
        for (auto p : a) {
            answer.push_back(p);
        }
        answer.pop_back();
        len += b;
    }
    answer.push_back(poi.back());
    return {answer, len};
}

int Widget::calculateDistance(const std::vector<std::vector<int>> &graph, const std::vector<int> &path) {
    int totalDistance = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        totalDistance += graph[path[i]][path[i + 1]];
    }
    return totalDistance;
}

std::pair<std::vector<int>, int> Widget::dijkstra(const std::vector<std::vector<int>> &graph, int start, int end, const std::set<int> &avoid) {
    int n = graph.size();
    std::vector<int> dist(n, INT_MAX);
    std::vector<int> prev(n, -1);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u])
            continue;

        if (avoid.count(u))
            continue;

        for (int v = 0; v < n; ++v) {
            if (!avoid.count(v) && graph[u][v] != INT_MAX) {
                int newDist = dist[u] + graph[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    prev[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    std::vector<int> path;
    for (int at = end; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    if (path.size() == 1 && path[0] != start)
        path.clear();

    int distance = calculateDistance(graph, path);
    return {path, distance};
}

std::pair<std::vector<int>, int> Widget::findShortestPath(const std::vector<std::vector<int>> &graph, int start, const std::vector<int> &targets) {
    std::vector<int> path;
    std::vector<int> bestPath;
    int minDistance = INT_MAX;

    std::vector<int> nodes = targets;
    std::sort(nodes.begin(),nodes.end());
    do {
        for(auto p:nodes){
            std::cout<<p<<' ';
        }
        std::cout<<"up\n";
        path.clear();
        path.push_back(start);
        path.insert(path.end(), nodes.begin(), nodes.end());
        // for(auto p:path){
        //     std::cout<<p<<' ';
        // }
        // std::cout<<'\n';
        int distance = calculateDistance(graph_, path);

        if (distance < minDistance) {
            minDistance = distance;
            bestPath = path;
        }
    } while (std::next_permutation(nodes.begin(), nodes.end()));

    return {bestPath, minDistance};
}
