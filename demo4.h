#ifndef DEMO4_H
#define DEMO4_H

#include <QWidget>
#include <vector>
#include <set>
#include <queue>
#include <utility>
#include <QString>

namespace Ui {
class Widget;
}

class Widget : public QWidget {
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_aButton_clicked();
    void on_pushButton_clicked();
    void on_pushButton2_clicked();

private:
    void floydWarshall(std::vector<std::vector<int>> &graph);
    std::pair<std::vector<int>, int> findShortestPath(const std::vector<std::vector<int>> &graph, int start, const std::vector<int> &targets);
    std::pair<std::vector<int>, int> dijkstra(const std::vector<std::vector<int>> &graph, int start, int end, const std::set<int> &avoid);
    int calculateDistance(const std::vector<std::vector<int>> &graph, const std::vector<int> &path);
    int getGraphIndex(const QString &nodeName) const;
    std::vector<int> getGraphIndices(const std::vector<QString> &nodeNames) const;
    std::pair<std::vector<int>, int> extend(std::vector<int> poi);
    bool hamiltonianCycleUtil(const std::vector<std::vector<int>> &graph, std::vector<int> &path, int pos, int V);
    std::vector<int> hamiltonianCycle(const std::vector<std::vector<int>> &graph, int start);

    Ui::Widget *ui;
    std::vector<QString> nodeNames;
    std::vector<std::vector<int>> graph;
    std::vector<std::vector<int>> graph_;
};

#endif // WIDGET_H
