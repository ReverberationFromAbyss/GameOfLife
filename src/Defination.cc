module;
export module GameOfLife:Defination;
import std;
import std.compat;
import Utils;

using namespace std;

namespace GameOfLife {

export class World;
export class Cell;

class Cell {
  /// Variables
protected:
private:
  World *m_parent_{nullptr};

  Utils::Position m_pos_;
  array<Utils::Position, 8> m_neighbors_;
  bool m_currentLivingStatus_{false};
  bool m_toBeLive_{false};

public:
  /// Methods
protected:
private:
  Cell() = default;
  bool Init(World *parent, Utils::Position pos, bool livingStatus);

public:
  ~Cell() = default;
  static Cell *Create(World *parent, Utils::Position pos = Utils::Position(),
                      bool livingStatus = false);
  Cell *NewInstance(World *parent);

  bool GetCurrentLivingStatus(void);
  void SetCurrentLivingStatus(bool livingStatus);

  void EvaluateNextStatus(void);
  void ForwardStatus(void);
};

class World {
  /// Variables
protected:
private:
  static World *s_instance_;
  bool m_initialized_{false};

  vector<vector<Cell *>> m_map_{};
  Utils::Position::position_x_t m_mapScaleXLimit_{};
  Utils::Position::position_y_t m_mapScaleYLimit_{};

public:
  /// Methods
protected:
private:
  World() = default;
  virtual bool Init(Utils::Position);

public:
  ~World();

  static World *Create(Utils::Position scale = Utils::Position(50, 50));
  static World *GetInstance(void);

  void SetLife(Utils::Position pos, Cell *cell);
  void SetLife(Utils::Position pos, bool livingStatus);
  void Update(void);
  Cell &GetLife(Utils::Position pos);

  Utils::Position GetMapScale(void);

  string ExportToString(void);
  vector<vector<Cell *>> ExportMap(void);
};
} // namespace GameOfLife
