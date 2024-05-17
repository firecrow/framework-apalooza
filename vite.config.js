import { defineConfig } from 'vite';
import { svelte } from '@sveltejs/vite-plugin-svelte';
import * as path from 'path';

export default defineConfig({
  build: {
    lib: {
      entry: path.resolve(__dirname, 'src/ui-svelte/input.svelte'),
      name: 'SvelteApp',
      fileName: (format) => `svelte-app.${format}.js`
    },
    outDir: "pre-dist",
    rollupOptions : {
      external: ['svelt-app'],
      output : {},
    },
  },
  plugins: [
    svelte({
      configFile: "svelte.config.js"
    })
  ]
});
