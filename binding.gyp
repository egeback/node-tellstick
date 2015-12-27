{
  "targets": [
    {
      "target_name": "tellstick",
      "sources": [ "tellstick-node.cpp", "device-node.cpp", "sensor-node.cpp" ],
      'cflags!': [ '-fno-exceptions' ],
      'cflags_cc!': [ '-fno-exceptions' ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "conditions": [
        ['OS=="mac"', {
            'include_dirs': [
                '/Library/Frameworks/TelldusCore.framework/Headers'
             ],
             'libraries': [
                '/Library/Frameworks/TelldusCore.framework'
            ]
        }],
        ['OS=="linux"', {
            'link_settings': {
                'libraries': [
          	         '-ltelldus-core',
                     '-ltellstick',
          	    ]
            }
         }],
         ['OS == "win"', {
            'defines': [
                '_WINDOWS=1',
            ],
            'link_settings': {
                'libraries': [
                    '-lTelldusCore'
                ],
                'library_dirs': [
                    'C:\\Program\\Telldus\\Development\\',
                    'C:\\Program Files\\Telldus\\Development\\',
                    'C:\\Program Files (x86)\\Telldus\\Development\\'
                ]
             },
             'include_dirs': [
                'C:\\Program\\Telldus\\Development\\',
                'C:\\Program Files\\Telldus\\Development\\',
                'C:\\Program Files (x86)\\Telldus\\Development\\'
            ]
         }]
        ]
    }
  ]
}
