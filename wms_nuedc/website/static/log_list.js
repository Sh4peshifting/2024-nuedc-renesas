$(document).ready(function () {

    $(function updateTable() {
        $.ajax({
            url: '/repository/get_log_info/', type: 'POST', success: function (receivedData) {
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

                const html = template(receivedData);
                $(".log-list-box").html(html);
            }
        });
    });

});