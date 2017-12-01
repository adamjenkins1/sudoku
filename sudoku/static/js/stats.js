var app = new Vue({
  el: '#app',
  data: {
    sudokuDataList: [],

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
        console.log(response);
      }.bind(this));
    }
  }
});
