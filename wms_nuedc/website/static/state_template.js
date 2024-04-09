$(document).ready(function () {

    function updateTable() {
        $.ajax({
            url: '/repository/get_repository_info', type: 'POST', success: function (receivedData) {

                let source = `<div class="entry">
        <div class="row row-cols-1 row-cols-md-3 g-4">
        {{#each cargo}}
        <div class="col">
            <div class="card border-secondary">
                <div class="card-body">
                    <h5 class="card-header mb-2" >{{this.cargo_list_id}}</h5>
                    <div class="card-text">
                    {{#if isEmpty}}
                    <div>状态：<span class="badge rounded-pill text-bg-primary">空闲</span></div>
                    {{else}}
                    <div>状态：<span class="badge rounded-pill text-bg-warning">有货</span></div>
                    {{/if}}
                    <div>货物ID：<span>{{this.cargo_id}}</div>
                    </div>
                </div>
            </div>
        </div>
        {{/each}}
        </div>
    </div>`;

                let template = Handlebars.compile(source);
                let context = receivedData;
                let html = template(context);
                $(".cargo-list-box").html(html);

                source = `{{#if isCarEmpty}}
    <div class="card border-primary mb-3">
        <div class="card-body text-primary">
            <h5 class="card-title">空闲</h5>
            <p class="card-text">当前运输车<span id="car_info">没有</span>运送货物</p>
        </div>
    {{else}}
        <div class="card border-warning mb-3">
        <div class="card-body text-warning">
            <h5 class="card-title">运送中</h5>
            <p class="card-text">当前运输车正在运送货物</p>
        </div>
        </div>
    {{/if}}    
    </div>`;

                template = Handlebars.compile(source);
                context = receivedData["context"];
                html = template(context);
                $(".car-state-box").html(html);

                const status = receivedData["status"];
                $('#alarm_disp').text(status["alarm_status"]);
                $('#cargo_disp').text(status["cargo_status"]);
                $('#temp_disp').text(status["temp_status"]);
                $('#hum_disp').text(status["hum_status"]);

            }
        });
    }

    setInterval(updateTable, 1000);


});