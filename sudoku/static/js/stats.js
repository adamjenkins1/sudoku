var count = 0;
var app = new Vue({
  el: '#app',
  data: {
    sudokuDataList: [],
    numRows: Number,
  },
  mounted() {
    this.loadData();

    setInterval(function () {
      this.loadData();
    }.bind(this), 5000);
  },
  methods: {
    loadData: function () {
      $.get('/jsondata', function (response) {
        this.sudokuDataList = response;
        this.numRows = this.sudokuDataList.rows.length;
        var dataPointsAC3 = this.sudokuDataList.rows.filter(function(e) {
          return e.algorithm == "AC3";
        }).map(function(e) {
          return {
              x: e.size,
              y: e.time
          };
        });

        var dataPointsGenetic = this.sudokuDataList.rows.filter(function(e) {
          return e.algorithm == "Genetic";
        }).map(function(e) {
          return {
              x: e.size,
              y: e.time
          };
        });

        Chart.defaults.global.animation.duration = 0;
        var color = Chart.helpers.color;
        var ctx = document.getElementById("canvas").getContext("2d");
        var scatterChart = new Chart(ctx, {
          type: 'scatter',
          data: {
            datasets: [{
              label: 'AC3',
              borderColor: window.chartColors.red,
              backgroundColor: color(window.chartColors.red).alpha(0.2).rgbString(),
              data: dataPointsAC3
            }, {
              label: 'Genetic',
              borderColor: window.chartColors.blue,
              backgroundColor: color(window.chartColors.blue).alpha(0.2).rgbString(),
              data: dataPointsGenetic
            }]
          },
          options: {
            scales: {
              xAxes: [{
                ticks: {
                  min: 4,
                  max: 16,
                },
                type: 'linear',
                position: 'bottom',
                scaleLabel: {
                  display: true,
                  labelString: 'Board Size',
                  fontSize: 15
                }
              }],
              yAxes: [{
                scaleLabel: {
                  display: true,
                  labelString: 'Time (ms)',
                  fontSize: 15
                }
              }]
            },
            title: {
              display: true,
              fontSize: 25,
              text: 'Board Size vs Time'
            },
          }
        });

        var AC3Time = dataPointsAC3.map(e => e.y);
        var AC3X = dataPointsAC3.map(e => e.x);

        var geneticTime = dataPointsGenetic.map(e => e.y);
        var geneticX = dataPointsGenetic.map(e => e.x);

        

        var geneticBox = {
          x: geneticX,
          y: geneticTime,
          name: 'Genetic',
          boxmean: true,
          type: 'box',
          orientation: 'v'
        };

        var AC3Box = {
          x: AC3X,
          y: AC3Time,
          name: 'AC3',
          boxmean: true,
          type: 'box',
          orientation: 'v'
        };

        var layout = {
          title: 'Board Size vs Time (ms) by Algorithm',
          yaxis: {
            title: 'Time (ms)',
          },
          xaxis: {
            title: 'Board Size',
          },
          boxmode: 'group'
        };

        var data = [AC3Box, geneticBox];
        Plotly.newPlot('box', data, layout);

      }.bind(this));
    }
  }
});

