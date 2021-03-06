#ifndef MBF_SP_HPP
#define MBF_SP_HPP

double mbf_sp(idx_t num_vertices, const redge_c &edges, vector<idx_t> &path,
              idx_t source, idx_t destination, bool &negative_cycle,
              unsigned weight_idx = 0) {
  negative_cycle = false;
  raw_edge edge;
  idx_t num_edges = edges.size();
  vector<idx_t> prev(num_vertices, -1);
  vector<double> dist(num_vertices, std::numeric_limits<double>::max());

  path.clear();
  dist[source] = 0;

  for (idx_t i = 0; i < (num_vertices - 1); ++i) {
    for (idx_t e = 0; e < num_edges; ++e) {
      edge = edges[e];

      if ((dist[edge.source] + edge.weights[weight_idx]) <
          dist[edge.destination]) {
        dist[edge.destination] = dist[edge.source] + edge.weights[weight_idx];
        prev[edge.destination] = edge.source;
      }
    }
  }

  for (idx_t e = 0; e < num_edges; ++e) {
    edge = edges[e];
    if ((dist[edge.source] + edge.weights[weight_idx]) <
        dist[edge.destination]) {
      negative_cycle = true;
      return 0;
    }
  }

  idx_t n = destination;
  double cost = dist[n];

  while (n != ((idx_t) - 1)) {
    path.push_back(n);
    n = prev[n];
  }

  std::reverse(path.begin(), path.end());

  return cost;
}

#endif
