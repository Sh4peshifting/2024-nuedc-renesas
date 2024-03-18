
$(document).ready(function () {

    function updateTable() {
        $.ajax({
            url: '/get_state',
            type: 'POST',
            success: function (receivedData) {
            }
        });
    }
    // setInterval(updateTable, 1000);

    let source =
        `<div class="entry">
        <div class="row row-cols-1 row-cols-md-3 g-4">
        {{#each cargo}}
        <div class="col">
            <div class="card border-secondary">
                <div class="card-body">
                    <h5 class="card-header">{{this.cargo_list_id}}</h5>
                    <p class="card-text">
                    {{#if isEmpty}}
                    <div>状态：<span class="badge rounded-pill text-bg-primary">空闲</span></div>
                    {{else}}
                    <div>状态：<span class="badge rounded-pill text-bg-warning">有货</span></div>
                    {{/if}}
                    <div>货物ID：<span>{{this.cargo_id}}</div>
                    </p>
                </div>
            </div>
        </div>
        {{/each}}
        </div>
    </div>`;

    let template = Handlebars.compile(source);
    let context = {
        cargo:
            [
                {
                    cargo_list_id: "1-1-1",
                    isEmpty: true,
                    cargo_id: "无"
                },
                {
                    cargo_list_id: "1-1-2",
                    isEmpty: true,
                    cargo_id: "无"
                },
                {
                    cargo_list_id: "1-1-3",
                    isEmpty: true,
                    cargo_id: "无"
                },
                {
                    cargo_list_id: "1-2-1",
                    isEmpty: false,
                    cargo_id: "无"
                },
                {
                    cargo_list_id: "1-2-2",
                    isEmpty: false,
                    cargo_id: "无"
                },
                {
                    cargo_list_id: "1-2-3",
                    isEmpty: true,
                    cargo_id: "无"
                },
                {
                    cargo_list_id: "1-3-1",
                    isEmpty: true,
                    cargo_id: "无"
                },
                {
                    cargo_list_id: "1-3-2",
                    isEmpty: false,
                    cargo_id: "无"
                },
                {
                    cargo_list_id: "1-3-3",
                    isEmpty: true,
                    cargo_id: "无"
                },
            ],
    };
    let html = template(context);
    $(".cargo-list-box").html(html);

    source = 
    `{{#if isCarEmpty}}
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
    context = { isCarEmpty: false };
    html = template(context);
    $(".car-state-box").html(html);

});