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

    let products = {
        basic: {
            name: 'Basic',
            price: 22.39,
            description: 'This is a basic model of the system with the type of features that everyday users would need.',
            qrt0units: 100,
        },
        advanced:  {
            name: 'Advanced',
            price: 56.32,
            description: 'This is a targeted at mass-subscription company users. It has the tracking and accountability features required in larger organizations.',
            qrt0units: 30,
        },
        pro:  {
            name: 'Pro',
            price: 224.19,
            description: 'This has the expert features that few will need, but it will be highly valued for what it delivers.',
            qrt0units: 10,
        }
    }

</script>

<template>
    <input value="hi from Vue" />
    <div class="products-info">
        <article v-for="prod in products">
            <h2>{{ prod.name }}</h2>
            <span>Price: {{ prod.price }}</span><br />
            <p>
                {{ prod.description}}
            </p>
        </article>
    </div>
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
