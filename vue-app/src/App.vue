<script setup lang="ts">
    const PROD_COLUMN = 0;
    const METRIC_COLUMN = 1;
    let data = {
        headers: ['Product', 'Metric', 'Qrtr0', 'Qrtr1','Qrtr2','Qrtr3','Qrtr4','Qrtr5','Qrtr6','Qrtr7'],
        rows: [
            ['Basic', 'Growth',0,0,0,0,0,0,0,0],
            ['Basic', 'Units',0,0,0,0,0,0,0,0],
            ['Basic', 'Price',0,0,0,0,0,0,0,0],
            ['Basic', 'Total',0,0,0,0,0,0,0,0],
            ['Advanced', 'Growth',0,0,0,0,0,0,0,0],
            ['Advanced', 'Units',0,0,0,0,0,0,0,0],
            ['Advanced', 'Price',0,0,0,0,0,0,0,0],
            ['Advanced', 'Total',0,0,0,0,0,0,0,0],
            ['Pro', 'Growth',0,0,0,0,0,0,0,0],
            ['Pro', 'Units',0,0,0,0,0,0,0,0],
            ['Pro', 'Price',0,0,0,0,0,0,0,0],
            ['Pro', 'Total',0,0,0,0,0,0,0,0],
        ]
    }
</script>

<template>
    <input value="hi from Vue" />
    <table class="data-points">
        <thead>
            <tr>
                <th v-for="label in data.headers">{{ label }}</th>
            </tr>
        </thead>
        <tr :class="'product-'+row[PROD_COLUMN]+' metric-'+row[METRIC_COLUMN]" v-for="row in data.rows">
            <td v-for="value in row">{{ value }}</td>
        </tr>
    </table>
</template>

<style scoped>
</style>
