$(document).ready(function () {

    function updateTable() {
        $.ajax({
            url: '/repository/get_repository_info/', type: 'POST', success: function (receivedData) {

                let source = `
        <div class="row row-cols-sm-3 row-cols-md-3 g-4">
        {{#each cargo}}
        <div class="col-sm-3" style="width: 8rem; margin-right: -20px">
            <div type="button" class="card border-secondary" onclick="get_cargo_id('{{this.cargo_list_id}}')">
                <div class="card-body">
                    <div style="margin: -7px">
                        <h5 class="card-header mb-2" >{{this.cargo_list_id}}</h5>
                    </div>
                    <div class="card-text mb">
                    {{#if isEmpty}}
                    <div class="d-flex justify-content-center align-items-center pt-1"><span class="badge rounded-pill text-bg-primary">空闲</span></div>
                    {{else}}
                    <div class="d-flex justify-content-center align-items-center pt-1"><span class="badge rounded-pill text-bg-warning">有货</span></div>
                    {{/if}}
                    <div class="d-flex justify-content-center align-items-center pt-1"><span>{{this.cargo_id}}</span></div>
                    </div>
                </div>
            </div>
        </div>
        {{/each}}
        </div>`;

                let template = Handlebars.compile(source);
                let context = receivedData;
                let html = template(context);
                $(".cargo-list-box").html(html);
            }
        });
    }
    updateTable();
    setInterval(updateTable, 1000);


});