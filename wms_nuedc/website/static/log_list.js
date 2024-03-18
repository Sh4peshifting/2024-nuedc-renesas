$(document).ready(function () {

    $(function updateTable() {
        $.ajax({
            url: '/get_log_list', type: 'POST', success: function (receivedData) {
                const source = `<div class="entry">
        <table class="table">
        <thead>
            <tr>
                <th scope="col">#</th>
                <th scope="col">人员</th>
                <th scope="col">时间</th>
                <th scope="col">操作</th>
                <th scope="col">备注</th>
            </tr>
        </thead>
        <tbody>
        {{#each log_list}}
            <tr>
                <th scope="row">{{this.id}}</th>
                <td>{{this.people}}</td>
                <td>{{this.time}}</td>
                <td>{{this.operation}}</td>
                <td>{{this.other}}</td>
            </tr>
        {{/each}}
        </tbody>
    </div>`;

                const template = Handlebars.compile(source);
                const context = {
                    log_list: [{
                        id: 1, people: "张三", time: "2021-07-01 12:00:00", operation: "入库", other: "无",
                    }, {
                        id: 2, people: "李四", time: "2021-07-01 12:00:00", operation: "出库", other: "无",
                    },],
                };
                const html = template(context);
                $(".log-list-box").html(html);
            }
        });
    });

});